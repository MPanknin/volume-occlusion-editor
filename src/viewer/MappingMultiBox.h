#pragma once
#include "mappingcollection.h"
class MappingMultiBox :
  public MappingCollection
{
public:
  MappingMultiBox(int numBins);
  virtual ~MappingMultiBox(void);
};

