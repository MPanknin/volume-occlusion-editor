#include "osg\TransferFunction"

#include "VisibilityMapper.h"
#include "HistogramCollection.h"
#include "Histogram.h"
#include "Logger.h"

// ====================================================
VisibilityMapper::VisibilityMapper(void)
{
}

// ====================================================
VisibilityMapper::~VisibilityMapper(void)
{
}
// ====================================================
void VisibilityMapper::GetCentroidList( const osg::TransferFunction1D* mapping, 
                                        HistogramCollection& collection,
                                        std::list<Centroid*>& centroids)
{
  FS();

  int numBins = collection.GetNumBins();

  std::list<Histogram*> histogramList = collection.GetHistList();
  std::list<Histogram*>::const_iterator histBegin = histogramList.begin();
  std::list<Histogram*>::const_iterator histEnd = histogramList.end();

  while (histBegin != histEnd)
  {
    Histogram* tmp = *histBegin;
    const unsigned char* histData = tmp->GetNormData();
    
    float sum = 0;
    for(int i = 0; i < numBins; i++)
    {
      sum += histData[i] * mapping->getColor(i).x();
    }

    float mean = sum / numBins;

    Centroid* centroid = new Centroid;
    centroid->value = (int)mean;
    centroid->intensity = tmp->GetMeta()->intensity;
    centroids.push_back(centroid);

    //Logger::Log("----");
    //Logger::Log("Histogram source", tmp->GetMeta()->posX, tmp->GetMeta()->posY, tmp->GetMeta()->posZ);
    //Logger::Log("Source intensity", tmp->GetMeta()->intensity);
    //Logger::Log("Centroid", centroid);

    histBegin++;
  }

  //Logger::Log("Number centroids", (int)centroids.size());
  
  FE();
}

// ====================================================
// ====================================================
// ====================================================
// ====================================================
// ====================================================
