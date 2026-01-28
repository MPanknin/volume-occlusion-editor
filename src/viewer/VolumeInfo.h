#ifndef VolumeInfo_h__
#define VolumeInfo_h__

#include "osg\Referenced"

class ConfigFile;

class VolumeInfo : public osg::Referenced
{
public:

  VolumeInfo();
  ~VolumeInfo();

  void Open(const char* path);
  void Save(const char* path);
  void Print();

  std::string file;
  int numBytes;

  int dimX;
  int dimY;
  int dimZ;

  float distX;
  float distY;
  float distZ;

  // seg y specific
  int inlineOffset;
  int crosslineOffset;
  int timeOffset;

  int sampleInterval;
};

#endif // VolumeInfo_h__
