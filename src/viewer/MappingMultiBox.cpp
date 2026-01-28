#include "MappingMultiBox.h"

#include "osg\TransferFunction"

#include "Logger.h"

//============================================================================
MappingMultiBox::MappingMultiBox(int numBins) : MappingCollection(numBins)
{
  int c1, c2, c3, c4;
  c1 = 120;
  c2 = 130;
  c3 = 140;
  c4 = 150;

  osg::Vec4 ONE(1, 1, 1, 1);
  osg::Vec4 ZERO(0, 0, 0, 0);

  osg::TransferFunction1D* mapping = new osg::TransferFunction1D;
  mapping->allocate(m_numBins);
  mapping->clear(ZERO);

  mapping->setColor((c1/4)-1, ZERO);
  mapping->setColor((c1/4), ONE);
  mapping->setColor((c1/4)+1, ZERO);

  mapping->setColor((c2/4)-1, ZERO);
  mapping->setColor((c2/4), ONE);
  mapping->setColor((c2/4)+1, ZERO);

  mapping->setColor((c3/4)-1, ZERO);
  mapping->setColor((c3/4), ONE);
  mapping->setColor((c3/4)+1, ZERO);

  mapping->setColor((c4/4)-1, ZERO);
  mapping->setColor((c4/4), ONE);
  mapping->setColor((c4/4)+1, ZERO);
  
  m_mappingList.push_back(mapping);
}

//============================================================================
//============================================================================
//============================================================================
MappingMultiBox::~MappingMultiBox(void)
{
}
//============================================================================
//============================================================================
//============================================================================
//============================================================================
//============================================================================

