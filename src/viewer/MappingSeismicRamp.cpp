#include "MappingSeismicRamp.h"

#include "osg/TransferFunction"

#include "Logger.h"

//============================================================================
MappingSeismicRamp::MappingSeismicRamp(int numBins) : MappingCollection(numBins)
{
	FS();

	osg::Vec4 ONE(1, 1, 1, 1);
	osg::Vec4 ZERO(0, 0, 0, 0);

	for (int x = 1; x < m_numBins / 2; x++)
	{
		osg::TransferFunction1D* mapping = new osg::TransferFunction1D;
		mapping->allocate(m_numBins);
		mapping->setColor(x-1, ONE);
		mapping->setColor(x, ZERO);

		mapping->setColor(numBins - x, ZERO);
		mapping->setColor(numBins, ONE);

		m_mappingList.push_back(mapping);

		Logger::Log("", 0, x, numBins - x, numBins);
	}

	Logger::Log("Num mappings generated", (int) m_mappingList.size());

	FE();
}

//============================================================================
MappingSeismicRamp::~MappingSeismicRamp(void)
{
}
//============================================================================
//============================================================================
//============================================================================
//============================================================================

