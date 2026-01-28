#ifndef PreCamera_h__
#define PreCamera_h__

namespace osg
{
  class Camera;
  class Image;
}

class RayCastTechnique;
class SyncCamCallBack;
class PostDrawCallback;

// ====================================================
class PreRenderCamera
{
public:
	PreRenderCamera(osg::Camera* mainCam, int w, int h, RayCastTechnique* technique);
  ~PreRenderCamera();

  osg::Camera* CreateRTCam(int xs, int ys);
  osg::Camera* GetCamera();

  osg::Image* GetDepthImage();
  SyncCamCallBack* GetSynCallBack();

protected:
	
private:
  osg::Camera* m_preCam;
  osg::Camera* m_mainCam;

  osg::Image* m_depthImg;

  SyncCamCallBack* m_syncCallback;
  PostDrawCallback* m_postDrawCallback;

};

#endif // PreCamera_h__