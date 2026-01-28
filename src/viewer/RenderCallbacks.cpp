#include "osgDB/WriteFile"
#include "osg/Camera"

#include "RayCastTechnique.h"
#include "RenderCallbacks.h"
#include "ApplicationPaths.h"

// ====================================================
PostDrawCallback::PostDrawCallback( osg::Image* src1, RayCastTechnique* technique )
{
  m_src1 = src1;
  m_technique = technique;
}
// ====================================================
void PostDrawCallback::operator()( const osg::Camera& camera ) const
{
  osgDB::writeImageFile(*m_src1, DEPTH_IMAGE);
  m_technique->UpdateTexture(RayCastTechnique::DEPTH, m_src1);
}
// ====================================================
SyncCamCallBack::SyncCamCallBack( osg::Camera* mainCam, osg::Camera* preCam )
{
  m_main = mainCam;
  m_pre = preCam;
}
// ====================================================
void SyncCamCallBack::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
  double left, right, bottom, top, znear, zfar;
  m_main->getProjectionMatrixAsFrustum(left, right, bottom, top, znear, zfar);
  m_pre->setProjectionMatrixAsFrustum(left, right, bottom, top, znear, zfar);

  Vec3f eye, center, up;
  m_main->getViewMatrixAsLookAt(eye, center, up);
  m_pre->setViewMatrixAsLookAt(eye, center, up);

  m_pre->setViewport(m_main->getViewport());
}
