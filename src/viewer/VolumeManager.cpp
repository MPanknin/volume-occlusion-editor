#pragma warning( disable : 4100 )

#include "VolumeManager.h"
#include "Logger.h"
#include "Helper.h"
#include <math.h>

//============================================================================
VolumeManager* VolumeManager::m_instance = 0;

//============================================================================
void VolumeManager::createEmpty( int w, int h, int d, GLenum format, GLenum type )
{
  m_volume = new osg::Image;
  m_volume->allocateImage(w, h, d, format, type); 

  m_occlusion = new osg::Image;
  m_occlusion->allocateImage(w, h, d, format, type); 

  for(int x = 0; x < w; x++)
  {
    for(int y = 0; y < h; y++)
    {
      for(int z = 0; z < d; z++)
      {
        m_volume->data(x, y, z)[0] = 0;
        m_occlusion->data(x, y, z)[0] = 1;
      }
    }
  }
  
}

//============================================================================
void VolumeManager::createGaussianNoise(int w, int h, int d, GLenum format, GLenum type)
{
  m_volume = new osg::Image;
  m_volume->allocateImage(w, h, d, format, type); 

  m_occlusion = new osg::Image;
  m_occlusion->allocateImage(w, h, d, format, type); 

  for(int x = 0; x < w; x++)
  {
    for(int y = 0; y < h; y++)
    {
      for(int z = 0; z < d; z++)
      {
        m_volume->data(x, y, z)[0] = Helper::RandomNormalDistribution(128, 10);
        m_occlusion->data(x, y, z)[0] = 1;
      }
    }
  }
}
//============================================================================
void VolumeManager::loadVolume(const std::string& volPath)
{
  m_volume = osgDB::readImageFile(volPath);
}
//============================================================================
void VolumeManager::restoreVolume()
{
  m_volume.release();
  m_volume->unref();
  m_volume = osgDB::readImageFile(m_restorePath);
}
//============================================================================
osg::Image* VolumeManager::getVolume()
{
  return m_volume;
}
//============================================================================
osg::Image* VolumeManager::getOccVolume()
{
  return m_occlusion;
}
////============================================================================
//osg::Image* VolumeManager::loadLUT(const char *filename)
//{
//  std::ifstream file(filename, std::ifstream::in | std::ifstream::binary);
//
//  if (!file.is_open())
//  {
//    return 0;
//  }
//
//  file.seekg(8, std::ios_base::cur);
//
//  const int lut_size = 256 * 4;
//  char *lut_data = new char[lut_size];
//  file.read(lut_data, lut_size);
//
//  osg::Image* transfer = new osg::Image();
//  transfer->allocateImage(256, 1, 1, GL_RGBA, GL_BYTE);
//
//  transfer->setImage(256, 1, 1, GL_TEXTURE_1D, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)lut_data, osg::Image::USE_NEW_DELETE);
//  
//  return transfer;
//}
//============================================================================
void VolumeManager::initSlice(int rad)
{
  using namespace osg;
  float occprev[1000];
  float addprev = 0;
  float subtprev = 0;
  float s = 2 * rad + 1;
  float w = s * s * s;

  int negRad = -(rad + 1);

  for (int z = 0; z < m_volume->r(); z++)
  {
    if(z % 5 == 0) printf("%i, ", z);
    for (int x = 0; x < m_volume->s(); x++)
    {
      for (int y = 0; y < m_volume->t(); y++)
      {
        Vec3f pos(x, y, z);
        if(x == 0 && y == 0)
        {
          float occ = getOcclusion(pos, rad);
          occprev[y] = occ;
          setVoxel(m_occlusion, pos, occ);
        }
        else if(x == 0)
        {
          float add = 0;
          float subt = 0;
          for(int i = -rad; i <=rad; i++)
          {
            for(int j = -rad; j <=rad; j++)
            {
              add += getVoxel(m_volume, pos + Vec3f(i, rad, j));
              subt += getVoxel(m_volume, pos + Vec3f(i, negRad, j));
            }
          }
          float diff = (add - subt) / w;
          float occ = diff + occprev[y - 1];
          occprev[y] = occ;
          setVoxel(m_occlusion, pos, occ);
        }
        else if(y == 0)
        {
          addprev = 0;
          subtprev = 0;
          for(int i = -rad; i <=rad; i++)
          {
            for(int j = -rad; j <=rad; j++)
            {
              addprev += getVoxel(m_volume, pos + Vec3f(rad, i, j));
              subtprev += getVoxel(m_volume, pos + Vec3f(negRad, i, j));
            }
          }
        }
        else
        {
          for(int i = -rad; i <=rad; i++)
          {
            addprev += getVoxel(m_volume, pos + Vec3f(rad, rad, i));
            addprev -= getVoxel(m_volume, pos + Vec3f(rad, negRad, i));

            subtprev += getVoxel(m_volume, pos + Vec3f(negRad, rad, i));
            subtprev -= getVoxel(m_volume, pos + Vec3f(negRad, negRad, i));
          }
        }
        if(x != 0)
        {
          float diff = (addprev - subtprev) / w;
          float occ = occprev[y];
          occ += diff;
          setVoxel(m_occlusion, pos, occ);
          occprev[y] = occ;
        }
      }
    }
  }  

  printf("\n");
}
//============================================================================
void VolumeManager::calcOcclusion(int radius, osg::Vec3f dir, int stepInc)
{
  osg::Vec3Array* add_mask = idx_add;
  osg::Vec3Array* rem_mask = idx_remove;
  float occold = 0;

  for(int y = 0; y < m_volume->t(); y++)
  {
    for(int x = 0; x < m_volume->s(); x++)
    {
      osg::Vec3f pos(x, y, stepInc);
      if(x == 0)
      {
        int occ = getOcclusion(pos, radius); 
        setVoxel(m_occlusion, pos, occ);
        occold = occ;
      }
      // continue sampling using the sampling masks
      else
      {
        osg::Vec3f prev(x - 1, y, stepInc);
        osg::Vec3f tmp;  

        float add = 0;
        float rem = 0;

        // first get the "old" voxels
        for(uint i = 0; i < rem_mask->size(); i++)
        {
          tmp = prev + (*rem_mask)[i];
          rem += getVoxel(m_volume, tmp);
        }
        // second get the "new" voxels
        for(uint i = 0; i < add_mask->size(); i++)
        {
          tmp = pos + (*add_mask)[i];
          add += getVoxel(m_volume, tmp);
        }

        // calc difference
        float diff = (add - rem) / m_sphereSamples;

        // get previous value from occlusion volume
        float occ = diff + occold;

        // write new voxel into occlusion volume
        setVoxel(m_occlusion, pos, occ);
        occold = occ;
      }
    }
  }
}
//============================================================================
int VolumeManager::getOcclusion(osg::Vec3f pos, int rad)
{
  m_sphereSamples = 0;
  int res = 0;

  for(int x = -rad; x <= rad; x++)
  {
    for(int y = -rad; y <= rad; y++)
    {
      for(int z = -rad; z <= rad; z++)
      {
        osg::Vec3f tmp(pos + osg::Vec3(x, y, z));
        ++m_sphereSamples;
        res += (int)getVoxel(m_volume, tmp);
      }
    }
  }
  // get weighting for voxels
  // needed for weighting of the sampling mask sampled voxels
  res /= m_sphereSamples;

  return (int)res;
}
//============================================================================
void VolumeManager::setVoxel(osg::Vec3f pos, int color)
{
  FS();

  int x = pos.x();
  int y = pos.y();
  int z = pos.z();

  unsigned char* data = m_volume->data(x, y, z);
  data[0] = (unsigned char)color;

  FE();
}
//============================================================================
void VolumeManager::setVoxel(osg::Image* image, osg::Vec3f pos, int color)
{
  if(color < 0) 
  {
    color = 0;
    std::cout << color << std::endl;
  }
  if(color > 255) 
    std::cout << color << std::endl;

  if(inside(image, pos)) // sanity check
  {
    int x = pos.x();
    int y = pos.y();
    int z = pos.z();

    image->data(x, y, z)[0] = (unsigned char)color;
  }
}
//============================================================================
osg::Vec2 VolumeManager::getSelectedVoxel()
{
  return osg::Vec2(m_selIntesity, m_selocclusion);
  m_dirtySelection = false;
}
//============================================================================
osg::Vec2 VolumeManager::getVoxel(osg::Vec3f pos)
{
  osg::Vec2 res(-1, -1);

  float xs = m_volume->s();
  float ys = m_volume->t();
  float zs = m_volume->r();

  float greatest = std::max(xs, std::max(ys, zs));

  // normalize size
  float xNormSize = (float) xs / greatest;
  float yNormSize = (float) ys / greatest;
  float zNormSize = (float) zs / greatest;
 
  pos.x() /= xNormSize;
  pos.y() /= yNormSize;
  pos.z() /= zNormSize;

  // increment number of texture fetches
  if(inside(m_volume, pos)) // sanity check
  {
    int x = pos.x() * m_volume->s();
    int y = pos.y() * m_volume->t();
    int z = pos.z() * m_volume->r();

    unsigned char* data = m_volume->data(x, y, z);

    switch(m_volume->getDataType())
    {
    case GL_UNSIGNED_BYTE:
      m_selIntesity = (int)(data[0]);
      m_selocclusion = (int)(data[1]);
      break;
    case GL_UNSIGNED_SHORT:
      m_selIntesity = (int)(((unsigned short*)data)[0]);
      m_selocclusion = (int)(((unsigned short*)data)[1]);
      break;
    }

    res.x() = m_selIntesity;
    res.y() = m_selocclusion;

    m_dirtySelection = true;
  }
  return res;
}

//============================================================================
int VolumeManager::getVoxel(osg::Image* image, osg::Vec3f pos)
{
  // increment number of texture fetches
  ++m_totalSamples; 
  if(inside(image, pos)) // sanity check
  {
    int res = image->data(pos.x(), pos.y(), pos.z())[0];
    return res;
  }
  return 0;
}
//============================================================================
void VolumeManager::genSamplingMasks(int rad, osg::Vec3 dir)
{
  
  // clear old mask
  idx_remove->clear();
  idx_add->clear();
  // sampling masks can be generated around the origin
  // as they serve as "offset" vectors only
  for(int x = -rad; x <= rad; x+=4)
  {
    for(int y = -rad; y <= rad; y+=4)
    {
      for(int z = -rad; z <= rad; z+=4)
      {
        osg::Vec3 pos(x, y, z);
        if(dir.x() != 0 && x == -rad)    
          idx_remove->push_back(pos);
        else if(dir.x() != 0 && x == rad)    
          idx_add->push_back(pos);

        else if(dir.z() != 0 && z == -rad)    
          idx_remove->push_back(pos);
        else if(dir.z() != 0 && z == rad)    
          idx_add->push_back(pos);
      } 
    }
  }
 
}
//============================================================================
void VolumeManager::drawSamplingMasks(osg::Geode* root)
{
  for(uint i = 0; i < idx_remove->size(); i++)
  {
    osg::Vec3 tmp = (*idx_remove)[i];
    osg::ShapeDrawable* shape = new osg::ShapeDrawable(new osg::Sphere(tmp, 0.3));
    shape->setColor(osg::Vec4(1, 0, 0, 1));
    root->addDrawable(shape);
  }
  for(uint i = 0; i < idx_add->size(); i++)
  {
    osg::Vec3 tmp = (*idx_add)[i];
    osg::ShapeDrawable* shape = new osg::ShapeDrawable(new osg::Sphere(tmp, 0.3));
    shape->setColor(osg::Vec4(0, 1, 0, 1));
    root->addDrawable(shape);
  }
}

//============================================================================
void VolumeManager::fillCube(const osg::Vec3f& min, const osg::Vec3f& max, int alpha)
{
  uchar* data;
  for(int z = min.z(); z < max.z(); z++)
  {
    for(int x = min.x(); x < max.x(); x++)
    {
      for(int y = min.y(); y < max.y(); y++)
      {
        data = m_volume->data(x, y, z);
        data[0] = (unsigned char)alpha;
      }
    }
  }
}
//============================================================================
void VolumeManager::fillCube(const osg::Vec3f& min, int len, int alpha)
{
  uchar* data;
  for(int z = min.z(); z < min.z() + len; z++)
  {
    for(int x = min.x(); x < min.x() + len; x++)
    {
      for(int y = min.y(); y < min.y() + len; y++)
      {
        data = m_volume->data(x, y, z);
        data[0] = (unsigned char)alpha;
      }
    }
  }
}

//============================================================================
void VolumeManager::fillSphere(const osg::Vec3f& center, float radius, int alpha)
{
  uchar* data;

  for(int z = 0; z < m_volume->r(); z++)
  {
    for(int x = 0; x < m_volume->s(); x++)
    {
      for(int y = 0; y < m_volume->t(); y++)
      {
        osg::Vec3f tmp(x, y, z);
        float dist = (center - tmp).length();
        if(dist <= radius)
        {
          data = m_volume->data(x, y, z);
          int val = alpha - dist;
          val = val > 255 ? 255: val;
          val = val < 0 ? 0: val;
          data[0] = (uchar)val;
        }
      }
    }
  }
}
//============================================================================
void VolumeManager::fillChannel(const osg::Vec3f& min, int len, int alpha)
{
  uchar* data;
  for(int z = min.z(); z < min.z() + 2; z++)
  {
    for(int x = min.x(); x < min.x() + len; x++)
    {
      for(int y = min.y(); y < min.y() + 4; y++)
      {

        for (int i = 0; i < 10; i++)
        {
          data = m_volume->data(x + i, y + sin((double)x / 10.0f) * 10, z);
          data[0] = (unsigned char)alpha;
        }
      }
    }
  }
}

//============================================================================
bool VolumeManager::inside(osg::Image* img, osg::Vec3f p)
{
  if(p.x() >= 0 && p.x() < img->s() &&
    p.y() >= 0 && p.y() < img->t() &&
    p.z() >= 0 && p.z() < img->r())
  {
    return true;
  }
  return false;
}
//============================================================================
bool VolumeManager::inSphere(osg::Vec3 pos, osg::Vec3 center, int rad)
{ 
  return (pos - center).length() < rad; 
}

