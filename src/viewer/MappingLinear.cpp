#include "MappingLinear.h"

#include "osg/TransferFunction"

#include "Logger.h"

//============================================================================
MappingLinear::MappingLinear(int numBins) : MappingCollection(numBins)
{
  FS();

  osg::Vec4 ONE(2, 2, 2, 2);
  osg::Vec4 ZERO(0, 0, 0, 0);

  for (int x = 0; x < numBins; x++)
  {
    osg::TransferFunction1D* mapping = new osg::TransferFunction1D;
    mapping->allocate(m_numBins);
    mapping->setColor(0, ZERO);
    mapping->setColor(m_numBins - x, ONE);
    mapping->setColor(m_numBins, ONE);
    m_mappingList.push_back(mapping);

    Logger::Log("", 0, numBins - x, numBins);
  }

  Logger::Log("Num mappings generated", (int) m_mappingList.size());

  FE();
}
//============================================================================
MappingLinear::~MappingLinear(void)
{
}
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================
