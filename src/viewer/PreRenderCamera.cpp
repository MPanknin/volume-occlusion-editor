#include "osg/Camera"
#include "osg/Image"

#include "PreRenderCamera.h"
#include "RenderCallbacks.h"
#include "Logger.h"

using namespace osg;

// ====================================================
PreRenderCamera::PreRenderCamera( Camera* mainCam, int w, int h, RayCastTechnique* technique )
{
  FS();

  m_mainCam = mainCam;

  m_depthImg = new Image();
  m_depthImg->allocateImage(w, h, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);

  m_preCam = CreateRTCam(w, h);
  m_preCam->setViewport(0, 0, w, h);
  m_preCam->attach(Camera::DEPTH_BUFFER, m_depthImg);

  m_postDrawCallback = new PostDrawCallback(m_depthImg, technique);
  m_preCam->setPostDrawCallback(m_postDrawCallback);

  m_syncCallback = new SyncCamCallBack(m_mainCam, m_preCam);

  FE();
}
// ====================================================
PreRenderCamera::~PreRenderCamera()
{
  //delete m_syncCallback;
  //delete m_postDrawCallback;
}
// ====================================================
Camera* PreRenderCamera::CreateRTCam( int xs, int ys )
{
  FS();

  Camera* camera = new Camera;

  camera->setClearColor(Vec4(0.3, 0.3, 0.3, 0));
  camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  camera->setComputeNearFarMode(Camera::DO_NOT_COMPUTE_NEAR_FAR);
  camera->setReferenceFrame(Transform::ABSOLUTE_RF);
  camera->setRenderOrder(Camera::PRE_RENDER);
  camera->setRenderTargetImplementation(Camera::FRAME_BUFFER_OBJECT);
  camera->setDrawBuffer(GL_DEPTH_COMPONENT);
  camera->setReadBuffer(GL_DEPTH_COMPONENT);

  FE();

  return camera;
}
// ====================================================
Camera* PreRenderCamera::GetCamera()
{
  return m_preCam;
}
// ====================================================
SyncCamCallBack* PreRenderCamera::GetSynCallBack()
{
  return m_syncCallback;
}
// ====================================================
Image* PreRenderCamera::GetDepthImage()
{
  return m_depthImg;
}


// ====================================================

