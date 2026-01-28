#pragma once
#include "mappingcollection.h"
class MappingBasic :
  public MappingCollection
{
public:
  MappingBasic(int numBins);
  virtual ~MappingBasic(void);
};

