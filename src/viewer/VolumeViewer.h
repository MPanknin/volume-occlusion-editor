#ifndef VolumeViewer_h__
#define VolumeViewer_h__

#include "osgViewer/Viewer"

#include <osg/Object>

#include "VoxelSlice.h"
#include "VolumeInfo.h"
#include "RayCastTechnique.h"

namespace osgViewer
{
  class Viewer;
}

namespace osg
{
  template <typename T> class ref_ptr; 
  class Node;
  class Group;
}

namespace osgVolume
{
  class ImageLayer;
  class Volume;
  class Locator;
}

namespace osgGA
{
  class TrackballManipulator;
}

class PreRenderCamera;
class UIContainer;
class VolumeInfo;

class VolumeViewer : public osg::Referenced
{
public:
	VolumeViewer(UIContainer* container);
	~VolumeViewer();

	bool Init(osg::ref_ptr<VolumeInfo> volInfo);
  void Refresh();
	void Finish();

  bool IsRealized();
  void Frame();
  void Run();
  
  osgVolume::ImageLayer* CreateLayer(osg::ref_ptr<VolumeInfo> volInfo);

  void SetSceneData(osg::Node* scene);
  void UpdateTexture(RayCastTechnique::TexChannel target, Image* image);
  void UpdatePoly(int target, int num, float* vertx, float* verty);

  void ToggleTransferFunction(bool active);
  void ToggleRenderer(bool active);
  void ToggleIso(bool active);
  void TogglePhong(bool active);
  void ToggleOcclusion(bool active);

  void MoveLine(VoxelSlice::LineType type, float d, const char* label);
  void ToggleLine(VoxelSlice::LineType type, bool visible);

  void SetIntensityMult(float multiplier);
  void SetIsoValue(float iso);
  void SetClipping(RayCastTechnique::ClippingTarget target, float val);
  void SetClearColor(osg::Vec4 color);
  
  osg::ref_ptr<osg::Image> GetVolImage() const;
  osg::ref_ptr<osgViewer::Viewer> GetViewer();
  osg::ref_ptr<VolumeInfo> GetVolInfo() const { return m_volInfo; }
  
  osg::Image* GetDepthImage();

  float GetXs() const;
  float GetYs() const;
  float GetZs() const;
  int GetNumBytes() const;

  bool InsideVolumeBounds(osg::Image* img, osg::Vec3f p);
  bool IsSelectionDirty() const;
  osg::Vec2 GetVoxel(osg::Vec3f pos);
  osg::Vec2* GetSelectedVoxel();

protected:
	
private:

  osg::ref_ptr<osgViewer::Viewer> m_viewer;
  osg::ref_ptr<osg::Group> m_root;
  osg::ref_ptr<osg::Image> m_volImage;
  osg::ref_ptr<RayCastTechnique> m_technique;
  osg::ref_ptr<osgGA::TrackballManipulator> m_manipulator;
  osg::ref_ptr<osgVolume::ImageLayer> m_layer;
  osg::ref_ptr<osgVolume::Locator> m_locator;
  osg::ref_ptr<osgVolume::VolumeTile> m_tile;
  osg::ref_ptr<osgVolume::Volume> m_volume;

  osg::ref_ptr<VolumeInfo> m_volInfo;
  osg::Group* m_scene;
  
  PreRenderCamera* m_depthCamera;
  UIContainer* m_container;

  float m_xs;
  float m_zs;
  float m_ys;

  float m_spaceX;
  float m_spaceY;
  float m_spaceZ;

  osg::Vec2* m_selectedVoxel;
  bool m_selectionDirty;
};

#endif // VolumeViewer_h__


