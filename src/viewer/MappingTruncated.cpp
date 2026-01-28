#include "MappingTruncated.h"

#include "osg\TransferFunction"

#include "Logger.h"

//============================================================================
MappingTruncated::MappingTruncated(int numBins) : MappingCollection(numBins)
{
  FS();

  for (int x = 0; x < numBins; x++)
  {
    osg::TransferFunction1D* mapping = new osg::TransferFunction1D;
    mapping->allocate(m_numBins);

    mapping->setColor(0, osg::Vec4(0, 0, 0, 0));
    mapping->setColor(m_numBins, osg::Vec4(1, 1, 1, 1));

    m_mappingList.push_back(mapping);
  }

  Logger::Log("Num mappings generated", (int) m_mappingList.size());

  FE();
}
//============================================================================
MappingTruncated::~MappingTruncated(void)
{
}
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================
