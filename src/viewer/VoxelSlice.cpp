#include <osg/ref_ptr>

#include <osg/Array>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Matrix>
#include <osg/PrimitiveSet>
#include <osg/StateSet>
#include <osg/Vec3>
#include <osgText/Font>
#include <osgText/Style>
#include <osgText/Text>

#include "VoxelSlice.h"
#include "Logger.h"

// ====================================================

using namespace osg;

void VoxelSlice::Init()
{
  FS();

  m_coords = new Vec3Array(4);
  m_root = new Group;
  m_textNodeBottom = new Geode;
  const char* name = 0;
  switch(m_type)
  {
  case VoxelSlice::TIMESLICE:
    name = "timeline";
    (*m_coords)[0] = Vec3d(0.0, 0.0, m_pos) * m_locMatrix;
    (*m_coords)[1] = Vec3d(1.0, 0.0, m_pos) * m_locMatrix;
    (*m_coords)[2] = Vec3d(1.0, 1.0, m_pos) * m_locMatrix;
    (*m_coords)[3] = Vec3d(0.0, 1.0, m_pos) * m_locMatrix;
    break;
  case VoxelSlice::CROSSLINE:
    name = "crossline";
    (*m_coords)[0] = Vec3d(m_pos, 0.0, 0.0) * m_locMatrix;
    (*m_coords)[1] = Vec3d(m_pos, 1.0, 0.0) * m_locMatrix;
    (*m_coords)[2] = Vec3d(m_pos, 1.0, 1.0) * m_locMatrix;
    (*m_coords)[3] = Vec3d(m_pos, 0.0, 1.0) * m_locMatrix;
    break;
  case VoxelSlice::INLINE:
    name = "inline";
    (*m_coords)[0] = Vec3d(0.0, m_pos, 0.0) * m_locMatrix;
    (*m_coords)[1] = Vec3d(1.0, m_pos, 0.0) * m_locMatrix;
    (*m_coords)[2] = Vec3d(1.0, m_pos, 1.0) * m_locMatrix;
    (*m_coords)[3] = Vec3d(0.0, m_pos, 1.0) * m_locMatrix;
    break;
  default:
    break;
  }

  CreateText("#--New Slice--#", Vec3(0, 0, 0) * m_locMatrix);
  
  m_elem = new DrawElementsUShort(GL_QUADS);
  m_elem->push_back(0);
  m_elem->push_back(1);
  m_elem->push_back(2);
  m_elem->push_back(3);

  m_geom = new Geometry;
  m_geom->setVertexArray(m_coords);
  m_geom->addPrimitiveSet(m_elem);

  m_wireGeom = new Geometry(*m_geom);

  m_plane = new Geode;
  m_plane->addDrawable(m_geom);
  m_plane->setName(name);

  m_root->addChild(m_plane);

  FE();
}
// ====================================================
VoxelSlice::VoxelSlice( Matrix matrix, LineType type )
{
  FS();
  m_locMatrix = matrix;
  m_type = type;
  m_pos = 0.5f;
  Init();
  SetActive(true);

  FE();
}
// ====================================================
void VoxelSlice::CreateText( const char* label, const Vec3& pos )
{
  std::string fontFile("arial.ttf");
  ref_ptr<osgText::Font> font = osgText::readFontFile(fontFile);
  ref_ptr<osgText::Style> style = new osgText::Style;
  
  m_textBottom = new osgText::Text;
  m_textBottom->setFont(font.get());
  m_textBottom->setCharacterSize(20.0f);
  m_textBottom->setAutoRotateToScreen(true);
  m_textBottom->setText(label);
  m_textBottom->setPosition(pos);
  m_textBottom->setAlignment(osgText::TextBase::CENTER_CENTER);
  m_textBottom->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
  m_textBottom->setAxisAlignment(osgText::TextBase::SCREEN); 

  m_textNodeBottom = new Geode;
  m_textNodeBottom->addDrawable(m_textBottom);

  m_textTop = new osgText::Text;
  m_textTop->setFont(font.get());
  m_textTop->setCharacterSize(20.0f);
  m_textTop->setAutoRotateToScreen(true);
  m_textTop->setText(label);
  m_textTop->setPosition(Vec3(1, 1, 1) - pos);
  m_textTop->setAlignment(osgText::TextBase::CENTER_CENTER);
  m_textTop->setCharacterSizeMode(osgText::TextBase::SCREEN_COORDS);
  m_textTop->setAxisAlignment(osgText::TextBase::SCREEN); 

  m_textNodeTop = new Geode;
  m_textNodeTop->addDrawable(m_textTop);

  ref_ptr<StateSet> stateset = m_textNodeBottom->getOrCreateStateSet();
  stateset->setMode(GL_DEPTH_TEST, StateAttribute::OFF);
  stateset = m_textNodeTop->getOrCreateStateSet();
  stateset->setMode(GL_DEPTH_TEST, StateAttribute::OFF);

}
// ====================================================
void VoxelSlice::Move(float d, const char* label)
{
  m_pos = float(d);

  Vec3d topPos;
  Vec3d bottomPos;
  switch(m_type)
  {
  case VoxelSlice::TIMESLICE:
    {
      (*m_coords)[0] = Vec3d(0.0, 0.0, m_pos) * m_locMatrix;
      (*m_coords)[1] = Vec3d(1.0, 0.0, m_pos) * m_locMatrix;
      (*m_coords)[2] = Vec3d(1.0, 1.0, m_pos) * m_locMatrix;
      (*m_coords)[3] = Vec3d(0.0, 1.0, m_pos) * m_locMatrix;
      bottomPos = Vec3d(0, 0, m_pos);
      topPos = Vec3d(1, 1, m_pos);
    }
    break;
  case VoxelSlice::CROSSLINE:
    {
      (*m_coords)[0] = Vec3d(m_pos, 0.0, 0.0) * m_locMatrix;
      (*m_coords)[1] = Vec3d(m_pos, 1.0, 0.0) * m_locMatrix;
      (*m_coords)[2] = Vec3d(m_pos, 1.0, 1.0) * m_locMatrix;
      (*m_coords)[3] = Vec3d(m_pos, 0.0, 1.0) * m_locMatrix;
      bottomPos = Vec3d(m_pos, 0, 0);
      topPos = Vec3d(m_pos, 1, 1);
    }
    break;
  case VoxelSlice::INLINE:
    {
      (*m_coords)[0] = Vec3d(0.0, m_pos, 0.0) * m_locMatrix;
      (*m_coords)[1] = Vec3d(1.0, m_pos, 0.0) * m_locMatrix;
      (*m_coords)[2] = Vec3d(1.0, m_pos, 1.0) * m_locMatrix;
      (*m_coords)[3] = Vec3d(0.0, m_pos, 1.0) * m_locMatrix;
      bottomPos = Vec3d(0, m_pos, 0);
      topPos = Vec3d(1, m_pos, 1);
    }
    break;
  }

  m_textBottom->setPosition(bottomPos * m_locMatrix);
  m_textTop->setPosition(topPos * m_locMatrix);
  m_textBottom->update();
  m_textTop->update();

  m_textBottom->setText(label);
  m_textTop->setText(label);

  m_elem->clear();
  m_elem->push_back(0);
  m_elem->push_back(1);
  m_elem->push_back(2);
  m_elem->push_back(3);

  m_geom->setVertexArray(m_coords);
  m_geom->removePrimitiveSet(0);
  m_geom->addPrimitiveSet(m_elem);

  m_wireGeom->setVertexArray(m_coords);
  m_wireGeom->removePrimitiveSet(0);
  m_wireGeom->addPrimitiveSet(m_elem);
}
// ====================================================
Geometry* VoxelSlice::GetWireGeom()
{
  return m_wireGeom;
}
// ====================================================
void VoxelSlice::SetActive( bool active )
{
  m_active = active;
}
// ====================================================
Group* VoxelSlice::GetGroup()
{
  return m_root;
}
// ====================================================
VoxelSlice::LineType VoxelSlice::GetType()
{
  return m_type;
}
// ====================================================
ref_ptr<Geode> VoxelSlice::GetTextNodeBottom() const
{
  return m_textNodeBottom;
}
// ====================================================
ref_ptr<Geode> VoxelSlice::GetTextNodeTop() const
{
  return m_textNodeTop;
}
