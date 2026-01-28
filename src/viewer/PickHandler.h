#ifndef PickHandler_h__
#define PickHandler_h__

#include <osgGA/GUIEventHandler>

#include "VoxelSlice.h"

namespace osg
{
  template <typename T> class ref_ptr; 
  class PositionAttitudeTransform;
}
namespace osgViewer
{
  class Viewer;
  class Group;
}
class VolumeViewer;

class PickHandler : public osgGA::GUIEventHandler 
{
public: 

  PickHandler(osg::Group* root, osg::ref_ptr<VolumeViewer> topView);
  ~PickHandler();
  bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
  bool pick(const double x, const double y, osgViewer::Viewer* viewer);

protected:
  osg::PositionAttitudeTransform* m_pickIndicator;
  VoxelSlice::LineType m_selectedSlice;
  
  osg::ref_ptr<VolumeViewer> m_topView;

  float m_x, m_y;
};

#endif // PickHandler_h__