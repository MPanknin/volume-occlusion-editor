#ifdef WIN32
#include <windows.h>
#endif

#include <assert.h>
#include <iosfwd>

#include "IL/il.h"
#include "IL/ilu.h"

#include "osg\ArgumentParser"
#include "osg\TransferFunction"
#include "osgDB\WriteFile"

#include "ApplicationPaths.h"
#include "Helper.h"
#include "Histogram.h"
#include "HistogramCollection.h"
#include "KMeansClusterer.h"
#include "Logger.h"
#include "MappingBasic.h"
#include "MappingLinear.h"
#include "MappingSeismicRamp.h"
#include "VisibilityMapper.h"
#include "VolumeManager.h"
#include "VolumeViewer.h"
#include "MappingMultiBox.h"
#include "MappingTruncated.h"

using namespace osg;

KMeansClusterer *gKMClusterer = NULL;

int num = 0;

Image* createBlackImage(int width, int height)
{
  Image* image = new osg::Image;
  image->allocateImage(width, height, 1, GL_RGB, GL_UNSIGNED_BYTE);

  // clear to black
  for(int x = 0; x < 256; x++)
  {
    for(int y = 0; y < 256; y++)
    {
      image->data(x, y, 0)[0] = 0;
      image->data(x, y, 0)[1] = 0;
      image->data(x, y, 0)[2] = 0;
    }
  }

  return image;
}

float PlotIt(HistogramCollection& collection, TransferFunction1D* mapping, const char* path = NULL)
{
  FS();

  // apply mapping to collection
  VisibilityMapper mapper;
  std::list<Centroid*> centroids;
  mapper.GetCentroidList(mapping, collection, centroids);

  // quick and dirty output for crossplot
  Image* hist = createBlackImage(256, 256);

  // reset iterator to beginning 
  std::list<Centroid*>::iterator centIt = centroids.begin();
  std::list<Centroid*>::iterator centEnd = centroids.end();
  while (centIt != centEnd)
  {
    Centroid* tmp = *centIt;
    centIt++;

    uchar* val = hist->data(tmp->intensity, tmp->value);
    if(val[0] < 255)
    {
      val[0] += 1;
      val[1] += 1;
      val[2] += 1;
    }
  }
  
  /*std::stringstream file;
  file << "cross_";
  file << num++;
  file << ".bmp";
  osgDB::writeImageFile(*hist, file.str());*/

  std::string filenamePrefix = "cross_";
  std::stringstream fileNum;
  fileNum << num++;
  std::string filenameSuffix = ".bmp";
  osgDB::writeImageFile(*hist, filenamePrefix + fileNum.str() + filenameSuffix);
  

  // convert centroids to Point2D 
  uchar thresh = 0;
  std::vector<Point2D> gDataPoints;

  for(int y=0; y<256; y++)
  {
    for(int x=0; x<256; x++)
    {
      uchar* val = hist->data(x, y);

      //if(*val != 0)
      if(*val > thresh)
      { //everything which is not black matters
        Point2D p;
        p.x = x;
        p.y = y;
        gDataPoints.push_back(p);	
      }
    }
  }

  Logger::Log("Number of data points", (int)gDataPoints.size());

  //------cluster data-------------------
  srand(12345);
  unsigned int initialNumClusters = 20;

  gKMClusterer = new KMeansClusterer(&gDataPoints);
  gKMClusterer->setNumClusters(initialNumClusters);

  gKMClusterer->clusterData();
  //gKMClusterer->mergeClusters();


  //-------write cluster data to image file------------

  //do some fancy coloring
  std::vector<ILubyte> r;
	std::vector<ILubyte> g;
	std::vector<ILubyte> b;

	float colStep = PI / (initialNumClusters - 1);

	for(int i=0; i<initialNumClusters; i++){
		r.push_back(255 * (0.5f * (sin(i * colStep + 0.78f)) + 1.0f));
		g.push_back(255 * (0.5f * (cos(i * colStep + PI)) + 1.0f));
		b.push_back(255 * (1.0f / PI * (i * colStep)));
	}

  Image* clustImg = createBlackImage(256, 256);

  for(int i=0; i<gDataPoints.size(); i++){
      clustImg->data(gDataPoints.at(i).x, gDataPoints.at(i).y, 0)[0] = r[gKMClusterer->getClusterInfo()[i]];
      clustImg->data(gDataPoints.at(i).x, gDataPoints.at(i).y, 0)[1] = g[gKMClusterer->getClusterInfo()[i]];
      clustImg->data(gDataPoints.at(i).x, gDataPoints.at(i).y, 0)[2] = b[gKMClusterer->getClusterInfo()[i]];
  }

  osgDB::writeImageFile(*clustImg, "clusterImg_" + fileNum.str() + filenameSuffix);

  Point2D mean;

  int numClusterPoints = gKMClusterer->getClusterPoints().size();

  //Logger::Log("Num cluster points", numClusterPoints);

  for(int i=0; i<numClusterPoints; i++)
  {
    mean += gKMClusterer->getClusterPoints().at(i);
  }
  mean /= numClusterPoints;

  float variance = 0.0f;
  for(int i=0; i<numClusterPoints; i++)
  {
    variance += gKMClusterer->getClusterPoints().at(i).getSquaredDist(mean);
  }
  variance /= numClusterPoints;

  Logger::Log("Mean", mean.x, mean.y);
  Logger::Log("Variance", variance);
  
  FE();

 /* hist->deallocateData();
  clustImg->deallocateData();*/

  return variance;
}
//============================================================================
void GenLocalHists(Image* volImg, HistogramCollection& collection, int radius, int numBins, int intervalMin, int intervalMax, std::string outFile)
{
  // update histogram after new volume file has been loaded
  osg::ref_ptr<osg::Image> hist = Helper::CreateLocalHistogram(volImg, 256, 100);
  osgDB::writeImageFile(*hist, HIST_IMAGE);

  osgDB::writeImageFile(*volImg, "temp/vol.dds");

  Logger::Log("Generating local histograms");
  Logger::Log("Radius", radius);
  Logger::Log("Num bins", numBins);
  Logger::Log("Interval", intervalMin, intervalMax);
  Logger::Log("Outfile", outFile);

  Helper::CreateLocalHistogram(volImg, radius, intervalMin, intervalMax, collection);

  // set source dimensions
  collection.SrcX(volImg->s());
  collection.SrcY(volImg->t());
  collection.SrcZ(volImg->r());

  Logger::Log("Export local histograms");
  std::ofstream file;
  file.open(outFile.c_str());
  file << collection;
  file.close();
}
//============================================================================
int main(int argc, char* argv[])
{
  Logger::SetLevel(Logger::TRACE);

  osg::ArgumentParser parser(&argc, argv);

  int mode = 1;
  parser.read("-mode", mode);

  int radius = 5;
  parser.read("-radius", radius);

  int numBins = 10;
  parser.read("-numBins", numBins);

  int intervalMin = 105;
  parser.read("-intervalMin", intervalMin);

  int intervalMax = 140;
  parser.read("-intervalMax", intervalMax);

  std::string outFile = "LocalHist.dat";
  parser.read("-outFile", outFile);

  std::string inFile = "temp/vol.dds";
  parser.read("-inFile", inFile);

  // histogram collection
  HistogramCollection collection(numBins);
  switch (mode)
  {
  case 1:
    // create a new data set and generate local
    // histograms with given parameters
    {
      //VolumeManager::i()->createGaussianNoise(250, 250, 50);
      //VolumeManager::i()->fillChannel(Vec3f(25, 150, 25), 150, 115);
      //VolumeManager::i()->fillChannel(Vec3f(50, 100, 10), 150, 120);
      //VolumeManager::i()->fillChannel(Vec3f(50, 150, 10), 150, 125);
      //VolumeManager::i()->fillChannel(Vec3f(50, 200, 10), 150, 130);

      VolumeManager::i()->loadVolume("temp/bonsai.dds");
      Image* volImg = VolumeManager::i()->getVolume();
      GenLocalHists(volImg, collection, radius, numBins, intervalMin, intervalMax, outFile);
    }
  	break;
  case 2:
    // load histogram file from disc
    collection.LoadHistogramFile(inFile.c_str());
    break;
  default:
    break;
  }

  // apply mapping to histogram collection
  MappingLinear mappingLinear(collection.GetNumBins());
  std::vector<TransferFunction1D*> list = mappingLinear.GetMappingList();
  std::vector<TransferFunction1D*>::iterator mappingBegin = list.begin();
  std::vector<TransferFunction1D*>::iterator mappingEnd = list.end();

  float maxVariance = 0;
  int maxMapping = 0;
  int idx = 0;

  while (mappingBegin != mappingEnd)
  {
    TransferFunction1D* tmp = *mappingBegin;
    float variance = PlotIt(collection, tmp);

    if(variance > maxVariance)
    {
      maxVariance = variance;
      maxMapping = idx;
    }
    idx++;
    mappingBegin++;
  }

  // output statistics
  Logger::Log("Max variance", maxVariance, Logger::INFO);
  Logger::Log("Idx max mapping", maxMapping, Logger::INFO);

  // get optimal mapping by idx
  TransferFunction1D* optMapping = mappingLinear.GetMappingByIndex(maxMapping);

  // construct resulting dual channel volume
  collection.WriteToVolume(VOL_IMAGE, optMapping);

  system("pause");
  return 0;
}
