#ifndef Helper_h__
#define Helper_h__

#include <osg/PolygonMode>
#include <osg/Vec3>

namespace osg
{
  class Vec2f;
  class Vec3f;
  class Node;
  class Image;
}

class HistogramCollection;
class Histogram;

class Helper
{
public:
  static long int GetFileSize(const char* path);
  static void SetDrawMode(osg::Node* srcNode, osg::PolygonMode::Mode mode);
  static bool PointInPoly(int nvert, float* vertx, float* verty, float testx, float testy);

  static osg::Image* CreateLocalHistogram(osg::Image* inImg, int outX = 256, int outY = 256);
  static osg::Image* CreateLocalHistogram(osg::Image* inImg, osg::Vec3f voxel, 
                                          int radius, int outX = 256, int outY = 256);
  
  static void CreateLocalHistogram(osg::Image* inImg, int rad, int minVal, int maxVal, HistogramCollection& histCollection);
  static void FillHistogram( osg::Image* inImg, osg::Vec3 param2, int radius, Histogram* tmp );

  static osg::Image* CreateCrossPlot(osg::Image* vol);

  static void SplitString(const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens);

  static double RandomNormalDistribution(double mu=0.0, double sigma=1.0);
};

#endif // IMAGEUTILS_Hs
