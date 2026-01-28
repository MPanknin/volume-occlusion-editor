#ifndef RAYCASTTECHNIQUE_H
#define RAYCASTTECHNIQUE_H

#include <iostream>

#include <osgVolume/VolumeTechnique>

#include "VoxelSlice.h"

namespace osg
{
  template <typename T> class ref_ptr; 
  class Geometry;
  class Geode;
  class Program;
  class Uniform;
  class Texture1D;
  class Texture2D;
  class Texture3D;
}

namespace osgUtil
{
  class UpdateVisitor;
  class CullVisitor;
  class IntersectionVisitor;
}

using namespace osg;

class RayCastTechnique : public osgVolume::VolumeTechnique
{
public:
  enum TexChannel
  {
    INTENSITY, TRANSFER, OCCLUSION, OPACITY, DEPTH
  };

  enum ClippingTarget
  {
    XMAX, XMIN, YMAX, YMIN, ZMAX, ZMIN
  };

  RayCastTechnique();
  RayCastTechnique(const RayCastTechnique&, const CopyOp& copyop = CopyOp::SHALLOW_COPY);

  META_Object(osgVolume, RayCastTechnique);

  virtual void init();
  virtual void update(osgUtil::UpdateVisitor* nv);
  virtual void cull(osgUtil::CullVisitor* nv);
  virtual void traverse(NodeVisitor& nv);
  virtual void intersect(osgUtil::IntersectionVisitor* iv);

  void SetupShader();
  void SetupVolume(){};
  void SetupTex3D();
  void SetupLines();
  void SetupGeom();
  Geometry* SetupCube();

  void CleanSceneGraph();
  void UpdatePoly(int target, int num, float* vertx, float* verty);
  void UpdateTexture(TexChannel target, Image* image);

  void SetClipping(ClippingTarget target, float val);
  void SetIntensityMult(float multiplier);
  void SetIsoValue(float iso);
  void SetSamples(int d);

  void ToggleSlices(bool active);
  void ToggleOcc(bool active);
  void ToggleIso(bool active);
  void ToggleRenderer(bool active);
  void TogglePhong(bool active);
  void ToggleTransferFunction(bool active);
  void ToggleLine(VoxelSlice::LineType type, bool visible);

  void Drag(bool drag);
  void InvertColor();

  void ResetLines();
  void MoveLine(VoxelSlice::LineType type, float d, const char* label);
  void HighlightLine(VoxelSlice::LineType type);

  VoxelSlice* m_tSlice;
  VoxelSlice* m_iSlice;
  VoxelSlice* m_xSlice;
  VoxelSlice* m_fSlice;

protected:

  virtual ~RayCastTechnique();

  Matrix m_locMatrix;

  ref_ptr<Image> m_volImage;
  ref_ptr<Image> m_occImage;

  ref_ptr<Texture3D> m_volTex3D;
  ref_ptr<Texture3D> m_occTex3D;
  ref_ptr<Texture2D> m_transTex2D;
  ref_ptr<Texture2D> m_opacityTex2D;
  ref_ptr<Texture2D> m_depthTex2D;

  ref_ptr<Program> m_volShader;
  ref_ptr<Program> m_lineShader;

  ref_ptr<Geode> m_wireBox;
  ref_ptr<Geode> m_wireSlice;
  ref_ptr<MatrixTransform> m_transform;

  ref_ptr<Geode> m_volCube;
  ref_ptr<Group> m_seisLines;
  ref_ptr<Geode> m_tLine;
  ref_ptr<Geode> m_iLine;
  ref_ptr<Geode> m_xLine;
  ref_ptr<Geode> m_fLine;

  ref_ptr<Uniform> m_raycastActive;
  ref_ptr<Uniform> m_sliceActive;
  ref_ptr<Uniform> m_invertColor;

  ref_ptr<Uniform> m_volumeSampler;
  ref_ptr<Uniform> m_transferFunction;
  ref_ptr<Uniform> m_opacitySampler;
  ref_ptr<Uniform> m_useTransfer;
  ref_ptr<Uniform> m_depthSampler;

  ref_ptr<Uniform> m_usePhong;
  ref_ptr<Uniform> m_useIso;
  ref_ptr<Uniform> m_occActive;  

  ref_ptr<Uniform> m_numSamples;
  ref_ptr<Uniform> m_IntensityMult;
  ref_ptr<Uniform> m_isv;

  ref_ptr<Uniform> m_volDimX;
  ref_ptr<Uniform> m_volDimY;
  ref_ptr<Uniform> m_volDimZ;

  int m_samples;
  float m_tPos;
  float m_inPos;
  float m_xPos;

  ref_ptr<Uniform> m_numSides;
  ref_ptr<Uniform> m_poly1X;
  ref_ptr<Uniform> m_poly1Y;

  ref_ptr<Uniform> m_poly2X;
  ref_ptr<Uniform> m_poly2Y;

  ref_ptr<Uniform> m_poly3X;
  ref_ptr<Uniform> m_poly3Y;

  ref_ptr<Uniform> m_clipXMax;
  ref_ptr<Uniform> m_clipXMin;

  ref_ptr<Uniform> m_clipYMax;
  ref_ptr<Uniform> m_clipYMin;

  ref_ptr<Uniform> m_clipZMax;
  ref_ptr<Uniform> m_clipZMin;
};

#endif
