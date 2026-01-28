#ifndef VolumeManager_h__
#define VolumeManager_h__

#include <iostream>

#include <osg/Image>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

typedef unsigned int uint;
typedef unsigned char uchar;

class VolumeManager
{
public:

  enum GenMode
  {
    BRUTE_FORCE, SAMPLING_MASK
  };

  // allocates two empty volumes
  void createEmpty(int w, int h, int d, GLenum format = GL_LUMINANCE, GLenum type = GL_UNSIGNED_BYTE);

  // gaussian noise intensities
  void createGaussianNoise(int w, int h, int d, GLenum format = GL_LUMINANCE, GLenum type = GL_UNSIGNED_BYTE);

  // loads given volume file. occlusion volume is copy constructed
  void loadVolume(const std::string& volPath);

  // restores original "uncropped" volume
  void restoreVolume();

  // return handle original volume
  osg::Image* getVolume();

  // return handle to occlusion volume
  osg::Image* getOccVolume();

  // insert a cube volume
  void fillCube(const osg::Vec3f& min, const osg::Vec3f& max, int alpha);
  void fillCube(const osg::Vec3f& min, int len, int alpha);

  // insert a sphere volume
  void fillSphere(const osg::Vec3f& center, float radius, int alpha);

  // insert a sphere volume
  void fillChannel(const osg::Vec3f& min, int len, int alpha);

  // manipulate single voxel
  void setVoxel(osg::Vec3f pos, int color);
  void setVoxel(osg::Image* image, osg::Vec3f pos, int color);

  // returns the intensity of a specific voxel
  osg::Vec2 getVoxel(osg::Vec3f pos);
  osg::Vec2 getSelectedVoxel();
  bool isSelectionDirty()
  { 
    if(m_dirtySelection == true) 
    {
      m_dirtySelection = false;
      return true; 
    }
    return false; 
  }

  // returns the intensity of a specific voxel
  int getVoxel(osg::Image* image, osg::Vec3f pos);

  // calculate brute force occlusion for one specific voxel.
  // currently used to initialize occlusion value for separate lines.
  // also used as reference in order to check fm results. 
  int getOcclusion(osg::Vec3f pos, int radius);

  // calculates occlusion for whole volume
  void calcOcclusion(int radius, osg::Vec3f dir, int stepInc = 1);

  // initial slice
  void initSlice(int radius);

  // generate sampling masks. 
  void genSamplingMasks(int rad, osg::Vec3 dir);

  // get number of samples taken inside sphere
  int getSphereSamples()
  {
    return m_sphereSamples;
  }

  // mask type
  enum MaskType
  {ADD, SUBTRACT};

  // get generated masks
  osg::Vec3Array* getMask(MaskType type)
  {
    switch(type)
    {
    case ADD:
      return idx_add;
    case SUBTRACT:
      return idx_remove;
    }
  };

  // draw sampling masks for debugging
  void drawSamplingMasks(osg::Geode* root);

  // helper
  bool inSphere(osg::Vec3 pos, osg::Vec3 center, int rad);
  bool inside(osg::Image* image, osg::Vec3f pos);

  // total number of texture fetches. 
  // increments in getVoxel()...
  inline long int total()
  { return m_totalSamples; }

  // ==================================================
  // singleton prop. returns instance
  static VolumeManager* i()
  {
    if(!m_instance) m_instance = new VolumeManager();
    return m_instance;
  }

  osgGA::TrackballManipulator* m_manipulator;
  osg::Camera* m_camera;

protected:
  // ctor protected due to singleton prop.
  VolumeManager()
  {
    m_voxelWeight = 0.0f;
    m_totalSamples = 0;
    m_selocclusion = 128;
    m_selIntesity = 128;
    idx_remove = new osg::Vec3Array;
    idx_add = new osg::Vec3Array;
  }

  ~VolumeManager(){}

  // original volume path
  std::string m_restorePath;

  // handle for original intensity volume
  osg::ref_ptr<osg::Image> m_volume;
  // handle for resulting occlusion volume
  osg::ref_ptr<osg::Image> m_occlusion;

  // the contribution weight of one single voxel
  // on N texture fetches this will be 1 / N
  float m_voxelWeight;
  int m_sphereSamples;

  // singleton prop instance
  static VolumeManager* m_instance;

  // left -> right sampling
  // subtraction mask
  osg::Vec3Array* idx_remove;
  // Vec3Array mask
  osg::Vec3Array* idx_add;

  // down -> up sampling
  // subtraction mask
  std::vector<osg::Vec3> idx_u;
  // addition mask
  std::vector<osg::Vec3> idx_d;

  // front -> back sampling
  // subtraction mask
  std::vector<osg::Vec3> idx_f;
  // addition mask
  std::vector<osg::Vec3> idx_b;

  // total samples taken
  long int m_totalSamples;

  // selected intensity & occlusion
  int m_selIntesity;
  int m_selocclusion;
  bool m_dirtySelection;
};

#endif