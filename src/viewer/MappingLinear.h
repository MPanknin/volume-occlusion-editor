#ifndef MappingLinear_h__
#define MappingLinear_h__

#include "MappingCollection.h"

class MappingLinear : public MappingCollection
{
public:
  MappingLinear(int numBins);
  virtual ~MappingLinear(void);
};

#endif // MappingLinear_h__
