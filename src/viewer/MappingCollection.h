#ifndef MappingCollection_h__
#define MappingCollection_h__

#include <list>
#include <vector>

namespace osg
{
  class TransferFunction1D;
}

class MappingCollection
{
public:
  MappingCollection(int numBins);
  virtual ~MappingCollection(void);

  const std::vector<osg::TransferFunction1D*>& GetMappingList()
  { return m_mappingList; }

  osg::TransferFunction1D* GetMappingByIndex(int idx)
  {
    if(idx < m_mappingList.size())
      return m_mappingList.at(idx);

    else return 0;
  }

  int GetNumBins() { return m_numBins; }

protected:
  std::vector<osg::TransferFunction1D*> m_mappingList;
  int m_numBins;
};

#endif // MappingCollection_h__
