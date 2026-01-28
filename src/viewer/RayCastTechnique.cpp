#include <osgDB\ReadFile>

#include <osgUtil\IntersectionVisitor>

#include <osgVolume\Locator>
#include <osgVolume\VolumeTechnique>
#include <osgVolume\VolumeTile>

#include <osg\Array>
#include <osg\Geode>
#include <osg\Geometry>
#include <osg\MatrixTransform>
#include <osg\PolygonMode>
#include <osg\PrimitiveSet>
#include <osg\Shader>
#include <osg\StateSet>
#include <osg\TexGen>
#include <osg\Texture2D>
#include <osg\Texture3D>
#include <osg\Texture>
#include <osg\Uniform>
#include <osg\Vec3d>
#include <osg\ref_ptr>

#include "Helper.h"
#include "Logger.h"
#include "RayCastTechnique.h"
#include "ApplicationPaths.h"

using namespace osgVolume;
using namespace osg;
// ====================================================
RayCastTechnique::RayCastTechnique()
{
  FS();
  m_volTex3D = new Texture3D;

  SetupShader();

  m_iSlice = 0;
  m_tSlice = 0;
  m_xSlice = 0;

  // ------------------------
  // clipping
  // ------------------------
  m_clipXMax = new Uniform("clipXMax", 1.0f);
  m_clipXMin = new Uniform("clipXMin", 0.0f);

  m_clipYMax = new Uniform("clipYMax", 1.0f);
  m_clipYMin = new Uniform("clipYMin", 0.0f);

  m_clipZMax = new Uniform("clipZMax", 1.0f);
  m_clipZMin = new Uniform("clipZMin", 0.0f);

  m_IntensityMult = new Uniform("intensityMult", 1.0f);

  // ------------------------
  // poly setup
  // ------------------------
  m_numSides = new Uniform("numSides", 4);
  m_poly1X = new Uniform("poly1X", Vec4(0, 0, 256, 256));
  m_poly1Y = new Uniform("poly1Y", Vec4(0, 256, 256, 0));

  m_poly2X = new Uniform("poly2X", Vec4(0, 0, 256, 256));
  m_poly2Y = new Uniform("poly2Y", Vec4(0, 256, 256, 0));

  m_poly3X = new Uniform("poly3X", Vec4(0, 0, 256, 256));
  m_poly3Y = new Uniform("poly3Y", Vec4(0, 256, 256, 0));

  // ------------------------
  // volume dimensions
  // ------------------------
  m_volDimX = new Uniform("volDimX", 100);
  m_volDimY = new Uniform("volDimY", 100);
  m_volDimZ = new Uniform("volDimZ", 100);

  // ------------------------
  // transfer function
  // ------------------------
  m_transTex2D = new Texture2D;
  m_transTex2D->setImage(osgDB::readImageFile(INITIAL_COLOR_TABLE));
  m_transferFunction = new Uniform("transfer", TRANSFER);

  m_opacityTex2D = new Texture2D;
  m_opacityTex2D->setImage(osgDB::readImageFile(OPACITY_TEXTURE));
  m_opacitySampler = new Uniform("opacity", OPACITY);

  m_volumeSampler = new Uniform("volume", INTENSITY);

  m_depthTex2D = new Texture2D;
  m_depthTex2D->setImage(osgDB::readImageFile(DEPTH_IMAGE));
  m_depthTex2D->setResizeNonPowerOfTwoHint(false);
  m_depthSampler = new Uniform("depth", DEPTH);

  m_occActive	= new Uniform("occActive", false);
  m_raycastActive	= new Uniform("active", false);
  m_useTransfer	= new Uniform("useTransfer", true);
  m_usePhong	= new Uniform("usePhong", false);
  m_useIso	= new Uniform("useIso", false);

  m_numSamples	= new Uniform("samples", m_samples);

  FE();
}
// ====================================================
RayCastTechnique::RayCastTechnique(const RayCastTechnique& fft,const CopyOp& copyop):
VolumeTechnique(fft,copyop){}
// ====================================================
RayCastTechnique::~RayCastTechnique()
{}

// ====================================================
void RayCastTechnique::init()
{
  FS();
  // ------------------------
  m_volImage = _volumeTile->getLayer()->getImage();
  m_volDimX->set(m_volImage->s());
  m_volDimY->set(m_volImage->t());
  m_volDimZ->set(m_volImage->r());

  // ------------------------
  ref_ptr<osgVolume::Locator> masterLocator = _volumeTile->getLocator();

  if (_volumeTile->getLayer() && !masterLocator)
  {masterLocator = _volumeTile->getLayer()->getLocator();}
  if (masterLocator)
  {m_locMatrix = masterLocator->getTransform();}

  // ------------------------
  // prepare
  m_samples = 512;

  // init vertices. this is just an initial 
  // setting to prevent an empty rendering window 
  // when user hits render volume the first time
  m_poly1X->set(Vec4(0, 0, 256, 256));
  m_poly1Y->set(Vec4(0, 256, 256, 0));

  m_poly2X->set(Vec4(0, 0, 256, 256));
  m_poly2Y->set(Vec4(0, 256, 256, 0));

  m_poly3X->set(Vec4(0, 0, 256, 256));
  m_poly3Y->set(Vec4(0, 256, 256, 0));

  SetupTex3D();
  SetupGeom();
   
  // ------------------------
  // volume
  // ------------------------
  ref_ptr<StateSet> stateset = m_volCube->getOrCreateStateSet();
  stateset->setAttribute(m_volShader);
  stateset->setMode(GL_ALPHA_TEST, StateAttribute::ON);
  stateset->setMode(GL_BLEND, StateAttribute::ON);
  stateset->setRenderingHint(StateSet::TRANSPARENT_BIN);

  ref_ptr<TexGen> texgen = new TexGen;
  texgen->setMode(TexGen::OBJECT_LINEAR);
  texgen->setPlanesFromMatrix(Matrix::inverse(m_locMatrix));
  stateset->setTextureAttributeAndModes(INTENSITY, texgen, StateAttribute::ON);

  // setup uniforms
  stateset->addUniform(m_occActive);
  stateset->addUniform(m_raycastActive);
  stateset->addUniform(m_useTransfer);
  stateset->addUniform(m_usePhong);
  stateset->addUniform(m_useIso);

  m_numSamples	= new Uniform("samples", m_samples);
  stateset->addUniform(m_numSamples);
  
  m_isv	= new Uniform("isv", 0.5f);
  stateset->addUniform(m_isv);

  // texture sampler
  stateset->setTextureAttributeAndModes(INTENSITY, m_volTex3D, StateAttribute::ON);
  stateset->addUniform(m_volumeSampler);
  stateset->setTextureAttributeAndModes(TRANSFER, m_transTex2D, StateAttribute::ON);
  stateset->addUniform(m_transferFunction);
  stateset->setTextureAttributeAndModes(OPACITY, m_opacityTex2D, StateAttribute::ON);
  stateset->addUniform(m_opacitySampler);
  stateset->setTextureAttributeAndModes(DEPTH, m_depthTex2D, StateAttribute::ON);
  stateset->addUniform(m_depthSampler);

  // selection poygons
  stateset->addUniform(m_numSides);
  stateset->addUniform(m_poly1X);
  stateset->addUniform(m_poly1Y);
  stateset->addUniform(m_poly2X);
  stateset->addUniform(m_poly2Y);
  stateset->addUniform(m_poly3X);
  stateset->addUniform(m_poly3Y);
  
  // clipping
  stateset->addUniform(m_clipXMax);
  stateset->addUniform(m_clipXMin);
  stateset->addUniform(m_clipYMax);
  stateset->addUniform(m_clipYMin);
  stateset->addUniform(m_clipZMax);
  stateset->addUniform(m_clipZMin);

  stateset->addUniform(m_IntensityMult);

  // volume dimensions
  stateset->addUniform(m_volDimX);
  stateset->addUniform(m_volDimY);
  stateset->addUniform(m_volDimZ);

  // ------------------------
  // slices
  // ------------------------
  stateset = m_seisLines->getOrCreateStateSet();
  stateset->setMode(GL_ALPHA_TEST, StateAttribute::ON);
  stateset->setAttribute(m_lineShader);
  stateset->setMode(GL_BLEND, StateAttribute::ON);
  stateset->setRenderingHint(StateSet::TRANSPARENT_BIN);
  stateset->setTextureAttributeAndModes(INTENSITY, texgen, StateAttribute::ON);

  // setup uniforms
  m_sliceActive	= new Uniform("active", true);
  m_invertColor	= new Uniform("invert", false);
  stateset->addUniform(m_sliceActive);
  stateset->addUniform(m_invertColor);
  stateset->addUniform(m_useTransfer);
  stateset->addUniform(m_occActive);

  // texture sampler
  stateset->setTextureAttributeAndModes(INTENSITY, m_volTex3D, StateAttribute::ON);
  stateset->addUniform(m_volumeSampler);
  stateset->setTextureAttributeAndModes(TRANSFER, m_transTex2D, StateAttribute::ON);
  stateset->addUniform(m_transferFunction);
  stateset->setTextureAttributeAndModes(OPACITY, m_opacityTex2D, StateAttribute::ON);
  stateset->addUniform(m_opacitySampler);

  stateset->setTextureAttributeAndModes(DEPTH, m_depthTex2D, StateAttribute::ON);
  stateset->addUniform(m_depthSampler);
  stateset->addUniform(m_IntensityMult);

  FE();
}
// ====================================================
void RayCastTechnique::HighlightLine(VoxelSlice::LineType type)
{
  if(type == VoxelSlice::NONE) return;
  VoxelSlice* target;
  switch(type)
  {
  case VoxelSlice::TIMESLICE:
    target = m_tSlice;
    break;
  case VoxelSlice::CROSSLINE:
    target = m_xSlice;
    break;
  case VoxelSlice::INLINE:
    target = m_iSlice;
    break;
  case VoxelSlice::FREEHAND:
    target = m_fSlice;
    break;
  }
  m_wireSlice->removeDrawables(0);
  m_wireSlice->addDrawable(m_tSlice->GetWireGeom());
  m_wireSlice->addDrawable(m_xSlice->GetWireGeom());
  m_wireSlice->addDrawable(m_iSlice->GetWireGeom());

}
// ====================================================
void RayCastTechnique::MoveLine(VoxelSlice::LineType type, float d, const char* label)
{
  if(type == VoxelSlice::NONE) return;
  VoxelSlice* target;
  
  switch(type)
  {
  case VoxelSlice::TIMESLICE:
    m_tSlice->Move(d, label);
    target = m_tSlice;
    break;
  case VoxelSlice::CROSSLINE:
    m_xSlice->Move(d, label);
    target = m_xSlice;
    break;
  case VoxelSlice::INLINE:
    m_iSlice->Move(d, label);
    target = m_iSlice;
    break;
  default:
    break;
  }
  m_wireSlice->removeDrawables(0);
  m_wireSlice->addDrawable(m_tSlice->GetWireGeom());
  m_wireSlice->addDrawable(m_xSlice->GetWireGeom());
  m_wireSlice->addDrawable(m_iSlice->GetWireGeom());
}
// ====================================================
void RayCastTechnique::ToggleLine( VoxelSlice::LineType type, bool visible)
{
  VoxelSlice* slice = 0;
  switch (type)
  {
  case VoxelSlice::CROSSLINE:
    slice = m_xSlice;
    break;
  case VoxelSlice::TIMESLICE:
    slice = m_tSlice;
    break;
  case VoxelSlice::INLINE:
    slice = m_iSlice;
    break;
  default:
    break;
  }

  if(slice)
  {
    slice->GetGroup()->setNodeMask(visible ? 0xffffffff : 0x0);
    slice->GetTextNodeBottom()->setNodeMask(visible ? 0xffffffff : 0x0);
    slice->GetTextNodeTop()->setNodeMask(visible ? 0xffffffff : 0x0);
    m_wireSlice->removeDrawable(slice->GetWireGeom());
  }
}
// ====================================================
void RayCastTechnique::ResetLines()
{
  m_iSlice->Move(50, "Inline");
  m_tSlice->Move(50, "Timeline");
  m_xSlice->Move(50, "Crossline");
}
// ====================================================
void RayCastTechnique::SetupGeom()
{
  m_volCube = new Geode;
  m_volCube->addDrawable(SetupCube());

  m_wireBox = new Geode;
  m_wireBox->addDrawable(SetupCube());
  m_wireBox->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::OFF);
  Helper::SetDrawMode(m_wireBox, PolygonMode::LINE);

  m_wireSlice = new Geode;
  m_wireSlice->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::OFF);
  Helper::SetDrawMode(m_wireSlice, PolygonMode::LINE);

  m_tSlice = new VoxelSlice(m_locMatrix, VoxelSlice::TIMESLICE);
  m_iSlice = new VoxelSlice(m_locMatrix, VoxelSlice::INLINE);
  m_xSlice = new VoxelSlice(m_locMatrix, VoxelSlice::CROSSLINE);
  
  m_seisLines = new Group;
  m_seisLines->addChild(m_tSlice->GetGroup());
  m_seisLines->addChild(m_iSlice->GetGroup());
  m_seisLines->addChild(m_xSlice->GetGroup());

  m_wireSlice->addDrawable(m_tSlice->GetWireGeom());
  m_wireSlice->addDrawable(m_xSlice->GetWireGeom());
  m_wireSlice->addDrawable(m_iSlice->GetWireGeom());

  m_transform = new MatrixTransform;
  m_transform->addChild(m_volCube);
  m_transform->addChild(m_wireSlice);
  m_transform->addChild(m_seisLines);
  m_transform->addChild(m_wireBox);

  m_transform->addChild(m_tSlice->GetTextNodeBottom());
  m_transform->addChild(m_iSlice->GetTextNodeBottom());
  m_transform->addChild(m_xSlice->GetTextNodeBottom());

  m_transform->addChild(m_tSlice->GetTextNodeTop());
  m_transform->addChild(m_iSlice->GetTextNodeTop());
  m_transform->addChild(m_xSlice->GetTextNodeTop());
}
// ====================================================
void RayCastTechnique::SetupShader()
{
  // ------------------------
  m_volShader = new Program;

  Shader* vertexShader = osgDB::readShaderFile(Shader::VERTEX, VERTEX_SHADER_VOL);
  if (vertexShader)
  {m_volShader->addShader(vertexShader);}

  Shader* fragmentShader = osgDB::readShaderFile(Shader::FRAGMENT, FRAGMENT_SHADER_VOL);
  if (fragmentShader)
  {m_volShader->addShader(fragmentShader);}

  // ------------------------
  m_lineShader = new Program;

  vertexShader = osgDB::readShaderFile(Shader::VERTEX, VERTEX_SHADER_SLICE);
  if (vertexShader)
  {m_lineShader->addShader(vertexShader);}

  fragmentShader = osgDB::readShaderFile(Shader::FRAGMENT, FRAGMENT_SHADER_SLICE);
  if (fragmentShader)
  {m_lineShader->addShader(fragmentShader);}
}
// ====================================================
void RayCastTechnique::SetupTex3D()
{
  Texture::InternalFormatMode internalFormatMode = Texture::USE_IMAGE_DATA_FORMAT;
  Texture::FilterMode minFilter = Texture::LINEAR;
  Texture::FilterMode magFilter = Texture::LINEAR;
  
  m_volTex3D->setNumMipmapLevels(0);
  m_volTex3D->setResizeNonPowerOfTwoHint(false);
  m_volTex3D->setFilter(Texture3D::MIN_FILTER, minFilter);
  m_volTex3D->setFilter(Texture3D::MAG_FILTER, magFilter);
  m_volTex3D->setWrap(Texture3D::WRAP_R, Texture3D::CLAMP_TO_EDGE);
  m_volTex3D->setWrap(Texture3D::WRAP_S, Texture3D::CLAMP_TO_EDGE);
  m_volTex3D->setWrap(Texture3D::WRAP_T, Texture3D::CLAMP_TO_EDGE);
  if(m_volImage->getPixelFormat()==GL_ALPHA || m_volImage->getPixelFormat()==GL_LUMINANCE12_ALPHA12)
  {
    m_volTex3D->setInternalFormatMode(Texture3D::USE_USER_DEFINED_FORMAT);
    m_volTex3D->setInternalFormat(GL_LUMINANCE16_ALPHA16);
  }
  else
  {
    m_volTex3D->setInternalFormatMode(internalFormatMode);
    m_volTex3D->setInternalFormat(GL_LUMINANCE16_ALPHA16);
  }
  m_volTex3D->setImage(m_volImage);

}
// ====================================================
void RayCastTechnique::SetupLines()
{}
// ====================================================
Geometry* RayCastTechnique::SetupCube()
{
  Geometry* geom = new Geometry;

  Vec3Array* coords = new Vec3Array(8);

  (*coords)[0] = Vec3d(0.0,0.0,0.0) * m_locMatrix;
  (*coords)[1] = Vec3d(1.0,0.0,0.0) * m_locMatrix;
  (*coords)[2] = Vec3d(1.0,1.0,0.0) * m_locMatrix;
  (*coords)[3] = Vec3d(0.0,1.0,0.0) * m_locMatrix;
  (*coords)[4] = Vec3d(0.0,0.0,1.0) * m_locMatrix;
  (*coords)[5] = Vec3d(1.0,0.0,1.0) * m_locMatrix;
  (*coords)[6] = Vec3d(1.0,1.0,1.0) * m_locMatrix;
  (*coords)[7] = Vec3d(0.0,1.0,1.0) * m_locMatrix;
  geom->setVertexArray(coords);

  DrawElementsUShort* drawElements = new DrawElementsUShort(GL_QUADS);
  // bottom
  drawElements->push_back(0);
  drawElements->push_back(1);
  drawElements->push_back(2);
  drawElements->push_back(3);

  // bottom
  drawElements->push_back(3);
  drawElements->push_back(2);
  drawElements->push_back(6);
  drawElements->push_back(7);

  // left
  drawElements->push_back(0);
  drawElements->push_back(3);
  drawElements->push_back(7);
  drawElements->push_back(4);

  // right
  drawElements->push_back(5);
  drawElements->push_back(6);
  drawElements->push_back(2);
  drawElements->push_back(1);

  // front
  drawElements->push_back(1);
  drawElements->push_back(0);
  drawElements->push_back(4);
  drawElements->push_back(5);

  // top
  drawElements->push_back(7);
  drawElements->push_back(6);
  drawElements->push_back(5);
  drawElements->push_back(4);

  geom->addPrimitiveSet(drawElements);

  Vec4Array* colors = new Vec4Array;
  colors->push_back(Vec4(1.0f, 1.0f, 1.0f, 1.0f) );

  geom->setColorArray(colors);
  geom->setColorBinding(Geometry::BIND_OVERALL);

  return geom;
}
// ====================================================
void RayCastTechnique::ToggleTransferFunction(bool active)
{
  m_useTransfer->set(active);
}

// ====================================================
void RayCastTechnique::ToggleRenderer(bool active)
{
  m_raycastActive->set(active);
}
// ====================================================
void RayCastTechnique::TogglePhong(bool active)
{
  m_usePhong->set(active);
}
// ====================================================
void RayCastTechnique::ToggleOcc( bool active )
{
  m_occActive->set(active);
}
// ====================================================
void RayCastTechnique::ToggleIso(bool active)
{
  m_useIso->set(active);
}
// ====================================================
void RayCastTechnique::SetIsoValue( float iso )
{
  m_isv->set(iso);
}
// ====================================================
void RayCastTechnique::ToggleSlices(bool active)
{
  m_sliceActive->set(active);
}
// ====================================================
void RayCastTechnique::InvertColor()
{
  bool active;
  m_invertColor->get(active);
  m_invertColor->set(!active);
}
// ====================================================
void RayCastTechnique::SetSamples(int d)
{
  m_numSamples->get(m_samples);
  m_samples += d;
  m_samples = m_samples < 16 ? 16: m_samples;
  m_samples = m_samples > 512 ? 512: m_samples;
  m_numSamples->set(m_samples);
}
// ====================================================
void RayCastTechnique::SetClipping(ClippingTarget target, float val)
{
  Uniform* targetLimit = 0;
  switch (target)
  {
  case XMAX:
    targetLimit = m_clipXMax;
  	break;
  case XMIN:
    targetLimit = m_clipXMin;
    break;
  case YMAX:
    targetLimit = m_clipYMax;
    break;
  case YMIN:
    targetLimit = m_clipYMin;
    break;
  case ZMAX:
    targetLimit = m_clipZMax;
    break;
  case ZMIN:
    targetLimit = m_clipZMin;
    break;
  }

  if(targetLimit)
    targetLimit->set((float)val / 100.0f);
}
// ====================================================
void RayCastTechnique::SetIntensityMult(float multiplier)
{
  m_IntensityMult->set(multiplier);
}
// ====================================================
void RayCastTechnique::Drag(bool drag)
{
  if(drag) m_numSamples->set(128);
  else m_numSamples->set(m_samples);
}
// ====================================================
void RayCastTechnique::UpdatePoly(int target, int num, float* vx, float* vy)
{
  if(target == 1)
  {
	m_poly1X->set(Vec4(vx[0], vx[1], vx[2], vx[3]));
	m_poly1Y->set(Vec4(vy[0], vy[1], vy[2], vy[3]));
  }
  else if(target == 2)
  {
	  m_poly2X->set(Vec4(vx[0], vx[1], vx[2], vx[3]));
	  m_poly2Y->set(Vec4(vy[0], vy[1], vy[2], vy[3]));
  }
  else if(target == 3)
  {
	  m_poly3X->set(Vec4(vx[0], vx[1], vx[2], vx[3]));
	  m_poly3Y->set(Vec4(vy[0], vy[1], vy[2], vy[3]));
  }

  m_numSides->set(4);
}
// ====================================================
void RayCastTechnique::UpdateTexture(TexChannel target, Image* image)
{
  switch(target)
  {
  case INTENSITY:
    m_volTex3D->setImage(image);
    m_volumeSampler->dirty();
    m_volDimX->set(image->s());
    m_volDimY->set(image->t());
    m_volDimZ->set(image->r());
    break;
  case TRANSFER:
    m_transTex2D->setImage(image);
    m_transferFunction->dirty();
    break;
  case OPACITY:
    m_opacityTex2D->setImage(image);
    m_opacitySampler->dirty();
    break;
  case DEPTH:
    m_depthTex2D->setImage(image);
    m_depthSampler->dirty();
    break;
  default:
    break;
  }
}

// ====================================================
void RayCastTechnique::update(osgUtil::UpdateVisitor* uv)
{
}
// ====================================================
void RayCastTechnique::intersect(osgUtil::IntersectionVisitor* iv)
{
  //if (m_transform.valid())
  //{
  //  m_transform->accept(*iv);
  //}
  if (m_seisLines.valid())
  {
    m_seisLines->accept(*iv);
  }
}

// ====================================================
void RayCastTechnique::cull(osgUtil::CullVisitor* cv)
{
  if (m_transform.valid())
  {
    m_transform->accept(*cv);
  }
}
// ====================================================
void RayCastTechnique::CleanSceneGraph()
{ notify(NOTICE)<<"RayCastTechnique::cleanSceneGraph()"<<std::endl; }
// ====================================================
void RayCastTechnique::traverse(NodeVisitor& nv)
{
  if (!_volumeTile) return;
  if (nv.getVisitorType()==NodeVisitor::UPDATE_VISITOR)
  {
    if (_volumeTile->getDirty()) _volumeTile->init();
    osgUtil::UpdateVisitor* uv = dynamic_cast<osgUtil::UpdateVisitor*>(&nv);
    if (uv)
    {
      update(uv);
      return;
    }
  }
  else if (nv.getVisitorType()==NodeVisitor::CULL_VISITOR)
  {
    osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(&nv);
    if (cv)
    {
      cull(cv);
      return;
    }
  }
  else if (nv.getVisitorType()==NodeVisitor::NODE_VISITOR)
  {
    osgUtil::IntersectionVisitor* iv = dynamic_cast<osgUtil::IntersectionVisitor*>(&nv);
    if (iv)
    {
      intersect(iv);
      return;
    }
  }
  if (_volumeTile->getDirty())
  {
    notify(INFO)<<"******* Doing init ***********"<<std::endl;
    _volumeTile->init();
  }
}






