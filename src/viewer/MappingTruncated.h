#ifndef MappingTruncated_h__
#define MappingTruncated_h__

#include "MappingCollection.h"

class MappingTruncated : public MappingCollection
{
public:
  MappingTruncated(int numBins);
  virtual ~MappingTruncated(void);
};

#endif // MappingTruncated_h__
