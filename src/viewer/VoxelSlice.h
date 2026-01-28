#ifndef VoxelSlice_h__
#define VoxelSlice_h__

#include "osgText\Text"

#include "osg\Array"
#include "osg\Matrix"
#include "osg\Vec3"

namespace osg
{
  template <typename T> class ref_ptr; 
  class Array;
  class Geode;
  class Group;
  class Geometry;
  class PrimitiveSet;
  class Program;
  class TexGen;
  class Texture3D;
  class DrawElementsUShort;
}

namespace osgText
{
  class Text;
}

class VoxelSlice
{
public:
  enum LineType
  { 
    INLINE, CROSSLINE, TIMESLICE, FREEHAND, NONE 
  };

  VoxelSlice(osg::Matrix matrix, LineType type);
  virtual ~VoxelSlice(){}
  
  void Init();
  void SetActive(bool active);
  void Move(float d, const char* label);
  void CreateText(const char* label, const osg::Vec3& pos);

  LineType GetType();

  osg::Geometry* GetWireGeom();
  osg::Group* GetGroup();
  osg::ref_ptr<osg::Geode> GetTextNodeBottom() const;
  osg::ref_ptr<osg::Geode> GetTextNodeTop() const;

protected:
  osg::Matrix m_locMatrix;

  osg::ref_ptr<osg::Geometry> m_geom;
  osg::ref_ptr<osg::Geometry> m_wireGeom;

  osg::ref_ptr<osg::Geode> m_plane;
  osg::ref_ptr<osg::Geode> m_textNodeBottom;
  osg::ref_ptr<osg::Geode> m_textNodeTop;

  osg::ref_ptr<osgText::Text> m_textBottom;
  osg::ref_ptr<osgText::Text> m_textTop;
  osg::ref_ptr<osg::Group> m_root;
  osg::ref_ptr<osg::Program> m_shader;
  osg::ref_ptr<osg::Vec3Array> m_coords;
  osg::ref_ptr<osg::DrawElementsUShort> m_elem;

  LineType m_type;
  bool m_active;

  float m_pos;
};

#endif // VoxelSlice_h__