#ifndef VisibilityMapper_h__
#define VisibilityMapper_h__

namespace osg
{
  template <typename T> class ref_ptr; 
  class TransferFunction1D;
}

class HistogramCollection;
class Histogram;
struct Centroid;

class VisibilityMapper
{
public:
  VisibilityMapper(void);
  virtual ~VisibilityMapper(void);

  void GetCentroidList(const osg::TransferFunction1D* mapping, 
                       HistogramCollection& collection, 
                       std::list<Centroid*>& centroids);

protected:

};

#endif // VisibilityMapper_h__
