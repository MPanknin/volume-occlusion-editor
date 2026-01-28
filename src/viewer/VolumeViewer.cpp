#include <iostream>

#include <osg/Geode>
#include <osg/Group>
#include <osg/Image>
#include <osg/Node>
#include <osg/ShapeDrawable>
#include <osg/ref_ptr>

#include <osgDB/ReadFile>

#include <osgGA/TrackballManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/Win32/GraphicsWindowWin32>

#include <osgVolume/Volume>

#include "UIContainer.h"

#include "KeyHandler.h"
#include "Logger.h"
#include "PickHandler.h"
#include "PreRenderCamera.h"
#include "VolumeInfo.h"
#include "VolumeViewer.h"
#include "ApplicationPaths.h"
#include "Helper.h"
#include "osgDB/WriteFile"

using namespace osg;
using namespace osgViewer;
using namespace osgVolume;

// ====================================================
VolumeViewer::VolumeViewer(UIContainer* container)
{
  FS();

  m_container = container;

  m_viewer = new osgViewer::Viewer;
  m_viewer->setUpViewInWindow(15, 77, 768, 768);
  m_viewer->addEventHandler(new osgViewer::StatsHandler);
  m_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);

  m_manipulator = new osgGA::TrackballManipulator();
  m_manipulator->setAutoComputeHomePosition(true);
  m_viewer->setCameraManipulator(m_manipulator);

  osgViewer::ViewerBase::Windows wins; 
  m_viewer->getWindows(wins); 
  osgViewer::GraphicsHandleWin32* hwnd = dynamic_cast<osgViewer::GraphicsHandleWin32*>(wins[0]); 
  
  // hide window styles (maximize, minimize and close box)
  SetWindowLong(hwnd->getHWND(), GWL_STYLE, ::GetWindowLong(hwnd->getHWND(), GWL_STYLE) & ~WS_MAXIMIZEBOX);
  SetWindowLong(hwnd->getHWND(), GWL_STYLE, ::GetWindowLong(hwnd->getHWND(), GWL_STYLE) & ~WS_MINIMIZEBOX);
  SetWindowLong(hwnd->getHWND(), GWL_STYLE, ::GetWindowLong(hwnd->getHWND(), GWL_STYLE) & ~WS_SYSMENU);

  // force window always on top
  SetWindowPos(hwnd->getHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | WS_EX_TOPMOST);

  ref_ptr<VolumeInfo> info = new VolumeInfo;
  info->Open(VOL_META_FILE);

  if(Init(info))
  {
    // osgvolume setup
    m_viewer->realize();
  }
  // done

  m_xs = m_ys = m_zs = 0;

  FE();
}
// ====================================================
VolumeViewer::~VolumeViewer()
{
  FS();
  m_viewer = 0;
  FE();
}
// ====================================================
void VolumeViewer::Finish()
{
  FS();
  m_viewer = 0;
  FE();
}
//============================================================================
void VolumeViewer::Refresh()
{
  //Vec3 eye, center, up;
  //m_viewer->getCamera()->getViewMatrixAsLookAt(eye, center, up);

  //Logger::Log("", eye.x(), eye.y(), eye.z());
  //Logger::Log("", center.x(), center.y(), center.z());
  //Logger::Log("", up.x(), up.y(), up.z());

  m_container->m_fileToLoad = m_volInfo;
  m_container->m_sceneDirty = true;
}
// ====================================================
bool VolumeViewer::Init(osg::ref_ptr<VolumeInfo> volInfo)
{
  FS();

  m_volInfo = volInfo;

  m_technique = new RayCastTechnique;

  m_tile = new osgVolume::VolumeTile();
  m_tile->setEventCallback(new osgVolume::PropertyAdjustmentCallback());
  m_tile->setVolumeTechnique(m_technique);

  m_volume = new osgVolume::Volume();
  m_volume->addChild(m_tile);

  m_layer = CreateLayer(volInfo);
  if(m_layer == 0)
  {
    Logger::Log("Layer is null");
    return 0;
  }

  m_tile->setLayer(m_layer);
  m_tile->setLocator(m_layer->getLocator());
  m_tile->setDirty(true);

  m_root = new osg::Group;
  m_scene = new osg::Group;

  m_scene->addChild(m_volume);
  m_root->addChild(m_scene);

  m_viewer->setSceneData(m_root);

  m_viewer->addEventHandler(new KeyHandler(m_technique, this));
  m_viewer->addEventHandler(new PickHandler(m_scene, this));

  m_manipulator = new osgGA::TrackballManipulator();
  m_manipulator->setAutoComputeHomePosition(true);
  //m_manipulator->setHomePosition(Vec3(0.5f, 0.5f, 2), Vec3(0.5f, 0.5f, 0), Vec3(0, 1, 0));
  m_viewer->setCameraManipulator(m_manipulator);
  
  m_depthCamera = new PreRenderCamera(m_viewer->getCamera(), 768, 768, m_technique);
  m_depthCamera->GetCamera()->addChild(m_scene);
  
  m_root->addChild(m_depthCamera->GetCamera());
  //m_root->setUpdateCallback(m_depthCamera->getSynCallBack());

  m_selectedVoxel = new osg::Vec2;
  m_selectionDirty = true;

  m_manipulator->home(0);
  m_viewer->realize();

  FE();

  return true;
}
// ====================================================
ImageLayer* VolumeViewer::CreateLayer(osg::ref_ptr<VolumeInfo> volInfo)
{
  FS();
  
  Logger::Log("Volume source", volInfo->file.c_str());

  // load volume data file
  m_volImage = osgDB::readImageFile(volInfo->file);
  
  if(m_volImage == 0) 
  {
    Logger::Log("Can not find input volume", volInfo->file);
    return 0;
  }

  // update histogram after new volume file has been loaded
  osg::ref_ptr<osg::Image> hist = Helper::CreateLocalHistogram(m_volImage, 256, 100);
  osgDB::writeImageFile(*hist, HIST_IMAGE);

  m_xs = m_volImage->s();
  m_ys = m_volImage->t();
  m_zs = m_volImage->r();

  m_spaceX = volInfo->distX;
  m_spaceY = volInfo->distY;
  m_spaceZ = volInfo->distZ;

  float greatest = max(m_xs, max(m_ys, m_zs));

  // normalize size
  float xNormSize = (float) m_xs / greatest;
  float yNormSize = (float) m_ys / greatest;
  float zNormSize = (float) m_zs / greatest;

  xNormSize *= volInfo->distX;
  yNormSize *= volInfo->distY;
  zNormSize *= volInfo->distZ;

  ref_ptr<RefMatrix> matrix;
  matrix = new RefMatrix(xNormSize, 0.0,   0.0,   0.0,
                        0.0,   yNormSize, 0.0,   0.0,
                        0.0,   0.0,   zNormSize, 0.0,
                        0.0,   0.0,   0.0,       1.0);

  // init layer
  ImageLayer* layer = new ImageLayer(0);
  layer->setImage(m_volImage);

  // set locator
  Locator* locator = new Locator(*matrix);
  layer->setLocator(locator);

  FE();
  return layer;
}

// ====================================================
void VolumeViewer::SetSceneData(osg::Node* scene)
{
  FS();
  m_viewer->setSceneData(scene);
  FE();
}
// ====================================================
void VolumeViewer::Frame()
{
  m_viewer->frame();
}
// ====================================================
void VolumeViewer::Run()
{
  m_viewer->run();
}
// ====================================================
bool VolumeViewer::IsRealized()
{
  return m_viewer->isRealized();

}
// ====================================================
void VolumeViewer::ToggleTransferFunction(bool active)
{
  m_technique->ToggleTransferFunction(active);
}
// ====================================================
void VolumeViewer::ToggleRenderer(bool active)
{
  m_technique->ToggleRenderer(active);
}
// ====================================================
void VolumeViewer::MoveLine(VoxelSlice::LineType type, float d, const char* label)
{
  if(m_technique)
    m_technique->MoveLine(type, d, label);
}
// ====================================================
void VolumeViewer::UpdateTexture(RayCastTechnique::TexChannel target, Image* image)
{
  m_technique->UpdateTexture(target, image);
}
// ====================================================
void VolumeViewer::ToggleLine( VoxelSlice::LineType type, bool visible )
{
  m_technique->ToggleLine(type, visible);
}
// ====================================================
float VolumeViewer::GetXs() const
{
  return m_xs;
}
// ====================================================
float VolumeViewer::GetYs() const
{
  return m_ys;
}
// ====================================================
float VolumeViewer::GetZs() const
{
  return m_zs;
}
// ====================================================
void VolumeViewer::SetClearColor( osg::Vec4 color )
{
  m_viewer->getCamera()->setClearColor(color);
}
// ====================================================
osg::Image* VolumeViewer::GetDepthImage()
{
  return m_depthCamera->GetDepthImage();
}
// ====================================================
void VolumeViewer::UpdatePoly( int target, int num, float* vertx, float* verty )
{
  m_technique->UpdatePoly(target, num, vertx, verty);
}
// ====================================================
void VolumeViewer::ToggleOcclusion( bool active )
{
  m_technique->ToggleOcc(active);
}
//============================================================================
bool VolumeViewer::IsSelectionDirty() const
{
  return m_selectionDirty;
}
//============================================================================
osg::Vec2* VolumeViewer::GetSelectedVoxel()
{
  m_selectionDirty = false;
  return m_selectedVoxel;
}
//============================================================================
osg::Vec2 VolumeViewer::GetVoxel( osg::Vec3f p )
{
  osg::Vec2 res(-1, -1);

  m_xs = m_volImage->s();
  m_ys = m_volImage->t();
  m_zs = m_volImage->r();

  float greatest = max(m_xs, max(m_ys, m_zs));

  // normalize size
  float xNormSize = (float) m_xs / greatest;
  float yNormSize = (float) m_ys / greatest;
  float zNormSize = (float) m_zs / greatest;

  p.x() /= xNormSize * m_spaceX;
  p.y() /= yNormSize * m_spaceY;
  p.z() /= zNormSize * m_spaceZ;

  int m_selIntesity = 0.0f;
  int m_selocclusion = 0.0f;

  // increment number of texture fetches
  if(InsideVolumeBounds(m_volImage, p)) // sanity check
  {
    int x = p.x() * m_volImage->s();
    int y = p.y() * m_volImage->t();
    int z = p.z() * m_volImage->r();

    unsigned char* data = m_volImage->data(x, y, z);

    switch(m_volImage->getDataType())
    {
    case GL_UNSIGNED_BYTE:
      m_selIntesity = (int)(data[0]);
      m_selocclusion = (int)(data[1]);
      break;
    case GL_UNSIGNED_SHORT:
      m_selIntesity = (int)(((unsigned short*)data)[0]);
      m_selocclusion = (int)(((unsigned short*)data)[1]);
      break;
    }

    res.x() = m_selIntesity;
    res.y() = m_selocclusion;

    m_selectedVoxel->x() = m_selIntesity;
    m_selectedVoxel->y() = m_selocclusion;

    m_selectionDirty = true;
  }
  return res;
}
//============================================================================
bool VolumeViewer::InsideVolumeBounds( osg::Image* img, osg::Vec3f p )
{
  if(p.x() >= 0 && p.x() < img->s() &&
    p.y() >= 0 && p.y() < img->t() &&
    p.z() >= 0 && p.z() < img->r())
  {
    return true;
  }
  return false;
}
//============================================================================
void VolumeViewer::SetClipping( RayCastTechnique::ClippingTarget target, float val )
{
  m_technique->SetClipping(target, val);
}
//============================================================================
void VolumeViewer::SetIntensityMult( float multiplier )
{
  m_technique->SetIntensityMult(multiplier);
}
//============================================================================
void VolumeViewer::TogglePhong( bool active )
{
  m_technique->TogglePhong(active);
}
//============================================================================
int VolumeViewer::GetNumBytes() const
{
  int numbytes = 1;
  switch(m_volImage->getDataType())
  {
  case GL_UNSIGNED_BYTE:
    numbytes = 1;
    break;
  case GL_UNSIGNED_SHORT:
    numbytes = 2;
    break;
  default:
    numbytes = 1;
  }
  return numbytes;
}
//============================================================================
void VolumeViewer::SetIsoValue( float iso )
{
  m_technique->SetIsoValue(iso);
}
//============================================================================
void VolumeViewer::ToggleIso( bool active )
{
  m_technique->ToggleIso(active);
}
//============================================================================

osg::ref_ptr<osg::Image> VolumeViewer::GetVolImage() const
{
  return m_volImage;
}
//============================================================================

osg::ref_ptr<osgViewer::Viewer> VolumeViewer::GetViewer()
{
  return m_viewer;
}

//============================================================================
//============================================================================
