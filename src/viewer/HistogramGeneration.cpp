//#include <iosfwd>
//
//#include "osg\ArgumentParser"
//#include "osg\TransferFunction"
//
//#include "osgDB\WriteFile"
//#include "osgDB\ReadFile"
//
//#include "ApplicationPaths.h"
//#include "Helper.h"
//#include "Histogram.h"
//#include "HistogramCollection.h"
//#include "Logger.h"
//#include "MappingBasic.h"
//#include "MappingLinear.h"
//#include "MappingSeismicRamp.h"
//#include "VisibilityMapper.h"
//#include "VolumeManager.h"
//
//using namespace osg;
//
////============================================================================
//int main(int argc, char* argv[])
//{
//  Logger::SetLevel(Logger::TRACE);
//
//  osg::ArgumentParser parser(&argc, argv);
//  std::string inFile = "";
//  parser.read("-inFile", inFile);
//
//  int radius = 5;
//  parser.read("-radius", radius);
//
//  int numBins = 10;
//  parser.read("-numBins", numBins);
//
//  int intervalMin = 100;
//  parser.read("-intervalMin", intervalMin);
//
//  int intervalMax = 170;
//  parser.read("-intervalMax", intervalMax);
//
//  std::string outFile = "LocalHist.dat";
//  parser.read("-outFile", outFile);
//
//  if(outFile.compare("") == 0)
//  {
//    Logger::Log("Outfile is invalid", outFile.c_str());
//    system("pause");
//    return 0;
//  }
//
//  if(inFile.compare("") == 0)
//  {
//    Logger::Log("Input file is invalid", inFile.c_str());
//    system("pause");
//    return 0;
//  }
//
//  std::string locHistFilename;
//  HistogramCollection collection(numBins);
//
//  //VolumeManager::i()->createGaussianNoise(250, 250, 50);
//  VolumeManager::i()->loadVolume(inFile.c_str());
//  //VolumeManager::i()->fillChannel(Vec3f(25, 150, 25), 150, 115);
//  //VolumeManager::i()->fillChannel(Vec3f(50, 100, 10), 150, 120);
//  //VolumeManager::i()->fillChannel(Vec3f(50, 150, 10), 150, 125);
//  //VolumeManager::i()->fillChannel(Vec3f(50, 200, 10), 150, 130);
//
//  //VolumeManager::i()->setVoxel(Vec3f(1, 0, 0), 100);
//  //VolumeManager::i()->setVoxel(Vec3f(1, 0, 1), 101);
//  //VolumeManager::i()->setVoxel(Vec3f(1, 1, 1), 111);
//
//  //VolumeManager::i()->setVoxel(Vec3f(2, 0, 0), 200);
//  //VolumeManager::i()->setVoxel(Vec3f(2, 0, 2), 202);
//  //VolumeManager::i()->setVoxel(Vec3f(2, 2, 2), 222);
//
//  //VolumeManager::i()->fillSphere(Vec3f(3, 3, 3), 2, 20);
//  Image* volImg = VolumeManager::i()->getVolume();
//  //osgDB::writeImageFile(*volImg, "temp/vol.dds");
//
//  //Image* volImg = osgDB::readImageFile(inFile.c_str());
//
//  //osg::ref_ptr<osg::Image> hist = Helper::CreateLocalHistogram(volImg, 256, 100);
//  //osgDB::writeImageFile(*hist, HIST_IMAGE);
//
//  Logger::Log("Generating local histograms");
//  Logger::Log("Radius", radius);
//  Logger::Log("Num bins", numBins);
//  Logger::Log("Interval", intervalMin, intervalMax);
//  Logger::Log("Outfile", outFile);
//  Logger::Log("Infile", inFile);
//
//  Helper::CreateLocalHistogram(volImg, radius, intervalMin, intervalMax, collection);
//
//  // set source dimensions
//  collection.SrcX(volImg->s());
//  collection.SrcY(volImg->t());
//  collection.SrcZ(volImg->r());
//
//  Logger::Log("Export local histograms");
//  std::ofstream file;
//  file.open(outFile.c_str());
//  file << collection;
//  file.close();
//
//  //system("pause");
//
//  return 1;
//}
