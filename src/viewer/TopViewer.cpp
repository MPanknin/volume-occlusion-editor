#include <iostream>

#include <osg/Geode>
#include <osg/Group>
#include <osg/Image>
#include <osg/Node>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/Win32/GraphicsWindowWin32>
#include <osgVolume/Volume>

#include "TopViewer.h"
#include "UIContainer.h"
#include "UIContainer.h"
#include "PreCamera.h"

using namespace osg;
using namespace osgViewer;
using namespace osgVolume;

// ====================================================
VolumeViewer::VolumeViewer()
{
  FS();

  m_root = 0;
  m_technique = 0;

  m_viewer = new osgViewer::Viewer;
  m_viewer->setUpViewInWindow(200, 200, 512, 512);
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

  m_viewer->realize();
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
ImageLayer* VolumeViewer::createLayer( const char* file )
{
  FS();
  Image* volData = osgDB::readImageFile(file);
  m_xs = volData->s();
  m_ys = volData->t();
  m_zs = volData->r();

  float greatest = max(m_xs, max(m_ys, m_zs));

  // normalize size
  float xNormSize = (float) m_xs / greatest;
  float yNormSize = (float) m_ys / greatest;
  float zNormSize = (float) m_zs / greatest;

  //xNormSize *= 1000;
  //yNormSize *= 1000;
  //zNormSize *= 1000;

  ref_ptr<RefMatrix> matrix;
  matrix = new RefMatrix(xNormSize, 0.0,   0.0,   0.0,
    0.0,   yNormSize, 0.0,   0.0,
    0.0,   0.0,   zNormSize, 0.0,
    0.0,   0.0,   0.0,       1.0);

  // init layer
  ImageLayer* layer = new ImageLayer(0);
  layer->setImage(volData);

  // set locator
  Locator* locator = new Locator(*matrix);
  layer->setLocator(locator);

  FE();
  return layer;
}

// ====================================================
void VolumeViewer::Init(const char* path)
{
  FS();

  m_root = new osg::Group;
  osg::Group* scene = new osg::Group;

  m_viewer->setSceneData(m_root);

  osg::ref_ptr<Volume> volume = new Volume();
  osg::ref_ptr<VolumeTile> tile = new VolumeTile();
  osg::ref_ptr<ImageLayer> layer = createLayer(path);

  tile->setLocator(layer->getLocator());
  tile->setLayer(layer);

  //
  m_technique = new RayCastTechnique;
  tile->setVolumeTechnique(m_technique);

  //
  volume->addChild(tile);
  scene->addChild(volume);
  m_root->addChild(scene);

  m_manipulator->home(0);
  m_viewer->realize();

  m_depthCamera = new PreRenderCamera(m_viewer->getCamera(), 512, 512, m_technique);
  m_depthCamera->getCamera()->addChild(scene);

  m_root->addChild(m_depthCamera->getCamera());
  m_root->setUpdateCallback(m_depthCamera->getSynCallBack());

  FE();
}
// ====================================================
void VolumeViewer::Finish()
{

}
// ====================================================
void VolumeViewer::setSceneData(osg::Node* scene)
{
  FS();
  m_viewer->setSceneData(scene);
  FE();
}
// ====================================================
bool VolumeViewer::isRealized()
{
  return m_viewer->isRealized();

}
// ====================================================
void VolumeViewer::frame()
{
  m_viewer->frame();
}
// ====================================================
void VolumeViewer::toggleTransferFunction()
{
  if(m_technique)
    m_technique->toggleTransferFunction();
}
// ====================================================
void VolumeViewer::toggleRenderer()
{  
  if(m_technique)
    m_technique->toggleRenderer();
}
// ====================================================
void VolumeViewer::moveLine(VoxelSlice::LineType type, float d, const char* label)
{
  if(m_technique)
    m_technique->moveLine(type, d, label);
}
// ====================================================
void VolumeViewer::updateTexture(RayCastTechnique::TexChannel target, Image* image)
{
  if(m_technique)
    m_technique->updateTexture(target, image);
}
// ====================================================
void VolumeViewer::toggleLine( VoxelSlice::LineType type, bool visible )
{  
  if(m_technique)
    m_technique->toggleLine(type, visible);
}
// ====================================================
float VolumeViewer::Xs() const
{
  return m_xs;
}
// ====================================================
float VolumeViewer::Ys() const
{
  return m_ys;
}
// ====================================================
float VolumeViewer::Zs() const
{
  return m_zs;
}
// ====================================================
void VolumeViewer::setClearColor( osg::Vec4 color )
{
  m_viewer->getCamera()->setClearColor(color);
}
// ====================================================
osg::Image* VolumeViewer::getDepthImage()
{
  return m_depthCamera->getDepthImage();
}
