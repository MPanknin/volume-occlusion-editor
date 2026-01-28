#include <osgUtil\LineSegmentIntersector>

#include <osgViewer\Viewer>

#include <osg\Group>
#include <osg\PositionAttitudeTransform>
#include <osg\Shape>
#include <osg\ShapeDrawable>
#include <osg\ref_ptr>

#include "PickHandler.h"
#include "Logger.h"
#include "VolumeViewer.h"

using namespace osg;
using namespace osgUtil;
using namespace osgGA;
using namespace osgViewer;

typedef LineSegmentIntersector LSI;

//============================================================================
PickHandler::~PickHandler()
{

}
//============================================================================
bool PickHandler::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
  Viewer* viewer = dynamic_cast<Viewer*>(&aa);
  if (!viewer)
    return false;

  switch(ea.getEventType())
  {
  case GUIEventAdapter::PUSH:
  case GUIEventAdapter::MOVE:
  {
    m_x = ea.getX();
    m_y = ea.getY();
    return false;
  }
  case GUIEventAdapter::RELEASE:
  {
    if (m_x == ea.getX() && m_y == ea.getY())
    {
      if (pick(ea.getXnormalized(), ea.getYnormalized(), viewer))
        return true;
    }
    return false;
  }
  default:
    return false;
  }
}
//============================================================================
bool PickHandler::pick(const double x, const double y, Viewer* viewer)
{
  if (!viewer->getSceneData())
    return false;

  ref_ptr<LSI> picker = new LSI(Intersector::PROJECTION, x, y);
  IntersectionVisitor iv(picker.get());

  viewer->getCamera()->accept(iv);
  if (picker->containsIntersections())
  {
    Vec3 p = picker->getFirstIntersection().getLocalIntersectPoint();
    Vec2 res = m_topView->GetVoxel(p);
    m_pickIndicator->setPosition(p);
    Logger::Log("Selected Voxel", (int)res.x(), (int)res.y());
  }
  else
  {
    Logger::Log("No intersection");
  }
  return false;
}
// ====================================================
PickHandler::PickHandler( osg::Group* root, ref_ptr<VolumeViewer> topView ) : m_x(0), m_y(0), m_selectedSlice(VoxelSlice::NONE)
{
  Sphere* sphere = new Sphere(Vec3(0,0,0), 0.005);
  ShapeDrawable* sphereDrawable = new ShapeDrawable(sphere);
  sphereDrawable->setColor(Vec4(0.9, 0.9, 0.9, 0.9));

  Geode* geode = new Geode;
  geode->addDrawable(sphereDrawable);

  m_pickIndicator = new PositionAttitudeTransform;
  m_pickIndicator->addChild(geode);

  root->addChild(m_pickIndicator);
  m_topView = topView;
}

// ====================================================
// ====================================================
// ====================================================