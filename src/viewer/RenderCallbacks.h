#ifndef RenderCallbacks_h__
#define RenderCallbacks_h__

namespace osg
{
  class Camera;
  class Image;
  class Node;
  class NodeVisitor;
}

class RayCastTechnique;

// ====================================================
class PostDrawCallback : public osg::Camera::DrawCallback
{
public:
  PostDrawCallback(osg::Image* src1, RayCastTechnique* technique);
  virtual void operator () (const osg::Camera& camera) const;

  osg::Image* m_src1;
  RayCastTechnique* m_technique;
};

// ====================================================
class SyncCamCallBack : public osg::NodeCallback
{
public:
  SyncCamCallBack(osg::Camera* mainCam, osg::Camera* preCam);
  virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

  osg::Camera* m_main;
  osg::Camera* m_pre;
};
#endif // RenderCallbacks_h__