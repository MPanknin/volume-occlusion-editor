#include "HistogramCollection.h"

#include <iostream>
#include <fstream>
#include <string>

#include "osg/TransferFunction"
#include "osgDB/WriteFile"

#include "ApplicationPaths.h"
#include "Logger.h"
#include "Helper.h"

//============================================================================
HistogramCollection::HistogramCollection( int numBins ) : m_numBins(numBins)
{
  m_srcX = -1;
  m_srcY = -1;
  m_srcZ = -1;
}
//============================================================================
HistogramCollection::~HistogramCollection(void)
{
  std::list<Histogram*>::iterator it;
  it = m_histList.begin();
  while (it != m_histList.end())
  {
    delete *it;
    it++;
  }
}
//============================================================================
Histogram* HistogramCollection::CreateHistogram()
{
  Histogram* temp = new Histogram(m_numBins);
  m_histList.push_back(temp);
  return temp;
}

//============================================================================
bool HistogramCollection::LoadHistogramFile( const char* path )
{
  FS();
  std::ifstream infile (path);
  if (!infile.is_open())
  {
    Logger::Log("Can not open Histogram file", Logger::WARNING);
    return false;
  }

  std::string line;
  int numBins = 0;
  while (infile.good())
  {
    getline(infile, line);
    // parse source dimensions
    if(line.find("source dimensions") != -1)
    {
      // substring start
      int s = line.find(":") + 1;
      // substring end
      int e = line.find("\n", s);

      std::string pos = line.substr(s, e - s).c_str();

      std::vector<std::string> tokens;
      Helper::SplitString(pos, ",", tokens);

      m_srcX = atoi(tokens[0].c_str());
      m_srcY = atoi(tokens[1].c_str());
      m_srcZ = atoi(tokens[2].c_str());
    }
    // parse number of bins
    else if(line.find("num bins") != -1)
    {
      int s = line.find(":") + 1;
      int e = line.find("\n");
      numBins = atoi(line.substr(s, e - s).c_str());
      m_numBins = numBins;
    }
    else if(line.find("v:") != -1)
    {
      // parse voxel coordinates
      int x, y, z, intensity;
      x = y = z = intensity = 0;

      // substring start
      int s = line.find("v:") + 2;
      // substring end
      int e = line.find("i:", s);

      std::string pos = line.substr(s, e - s).c_str();

      std::vector<std::string> tokens;
      Helper::SplitString(pos, ",", tokens);

      x = atoi(tokens[0].c_str());
      y = atoi(tokens[1].c_str());
      z = atoi(tokens[2].c_str());

      // parse source intensity
      {
        int s = line.find("i:") + 2;
        int e = line.find("d:", s);
        intensity = atoi(line.substr(s, e - s).c_str());
      }

      // construct new histogram  
      Histogram* tmp = CreateHistogram();
      tmp->SetIntensity(intensity);
      tmp->SetOrigin(x, y, z);

      s = line.find("d:") + 2;
      e = line.find("\n", s);
      std::string data = line.substr(s, e - s).c_str();

      tokens.clear();
      Helper::SplitString(data, ",", tokens);

      for (int i = 0; i < numBins; i++)
      {
        tmp->SetBinValue(i, atoi(tokens[i].c_str()));
      }
    }
  }

  Logger::Log("Histograms loaded", (int)m_histList.size());

  FE();
}

//============================================================================
void HistogramCollection::WriteToVolume(const char* path, osg::TransferFunction1D* mapping )
{
  FS();

  osg::Image* occImg = new osg::Image;
  occImg->allocateImage(m_srcX, m_srcY, m_srcZ, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE);

  int numBins = GetNumBins();

  std::list<Histogram*>::const_iterator histBegin = m_histList.begin();
  std::list<Histogram*>::const_iterator histEnd = m_histList.end();

  while (histBegin != histEnd)
  {
    Histogram* tmp = *histBegin;
    const unsigned char* histData = tmp->GetNormData();

    float sum = 0;
    for(int i = 0; i < numBins; i++)
    {
      // apply mapping to bins of our histogram
      sum += histData[i] * mapping->getColor(i).x();
    }

    // calc mean value
    float mean = sum / numBins;

    // get source position of voxel
    const HistogramMeta* meta = tmp->GetMeta();
    osg::Vec3 p(meta->posX, meta->posY, meta->posZ);

    // get target voxel
    unsigned char* data = occImg->data(p.x(), p.y(), p.z());
    // write source intensity into luminance channel
    data[0] = meta->intensity;
    // occlusion into alpha channel
    data[1] = (int)mean;

    histBegin++;
  }

  // save the resulting volume
  osgDB::writeImageFile(*occImg, path);

  // cretae crossplot. this is the actual occlusion spectrum
  osg::Image* hist = Helper::CreateCrossPlot(occImg);

  // save it
  osgDB::writeImageFile(*hist, OCC_SPECTRUM);

  FE();
}

//============================================================================
std::ostream&  operator<<(std::ostream &lhs, HistogramCollection &rhs)  
{
  if(rhs.SrcX() == -1 || rhs.SrcY() == -1 || rhs.SrcZ() == -1)
  {
    Logger::Log("Can not export histogram collection", Logger::CRITICAL);
    Logger::Log("Invalid dimensions", Logger::CRITICAL);
  }

  //DEBUG
  std::cout<<"writing "<<rhs.GetHistList().size()<<" histograms"<<std::endl;
  std::list<Histogram*>::const_iterator histIt = rhs.GetHistList().begin();
  std::list<Histogram*>::const_iterator histEnd = rhs.GetHistList().end();

  lhs << "source dimensions: " << rhs.SrcX() << ", " << rhs.SrcY() << ", " << rhs.SrcZ() << std::endl;
  lhs << "num bins: " << rhs.GetNumBins() << std::endl;
  
  while(histIt != histEnd)
  {
    int numBins = (*histIt)->GetNumBins();
    const unsigned char *data = (*histIt)->GetNormData();
    const HistogramMeta* tmpMeta = (*histIt)->GetMeta();
    
    lhs << "v: " << tmpMeta->posX << ", " << tmpMeta->posY << ", " << tmpMeta->posZ << ", ";
    lhs << "i: " << static_cast<int>(tmpMeta->intensity) << ", ";
    lhs << "d: ";
    
    for(int i=0; i<numBins; i++)
    {
      lhs<<static_cast<int>(*data++); //no idea why cast to int is needed

      if(i < (numBins - 1))
      {
        lhs<<",";
      }
    }

    lhs<<std::endl;
    histIt++;
  }

  return lhs;
}