#ifndef HistogramCollection_h__
#define HistogramCollection_h__

#include <list>

#include "Histogram.h"

namespace osg
{
  class TransferFunction1D;
}

class HistogramCollection
{
public:
  HistogramCollection(int numBins);
  virtual ~HistogramCollection(void);

  Histogram* CreateHistogram();
  const std::list<Histogram*>& GetHistList(){ return m_histList; }
  int GetNumBins() { return m_numBins; }
  bool LoadHistogramFile(const char* file);
  void SaveHistogramFile(const char* file);

  // save final result into volume
  // target file is defined in VOL_IMAGE
  void WriteToVolume(const char* path, osg::TransferFunction1D* mapping);

  int SrcX() const { return m_srcX; }
  void SrcX(int val) { m_srcX = val; }
  int SrcY() const { return m_srcY; }
  void SrcY(int val) { m_srcY = val; }
  int SrcZ() const { return m_srcZ; }
  void SrcZ(int val) { m_srcZ = val; }

protected:
  std::list<Histogram*> m_histList;
  int m_numBins;
  int m_srcX;
  int m_srcY;
  int m_srcZ;

};

std::ostream& operator<<(std::ostream &lhs, HistogramCollection &rhs);
#endif // HistogramCollection_h__
