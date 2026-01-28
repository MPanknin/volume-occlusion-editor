#include <windows.h>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/fstream>
#include <osg/Image>
#include <osg/ImageUtils>

#include "RawManager.h"
#include "Logger.h"
#include "Helper.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

using namespace osg;
using namespace std;

//============================================================================
struct ScaleOperator
{
  ScaleOperator():_scale(1.0f) {}
  ScaleOperator(float scale):_scale(scale) {}
  ScaleOperator(const ScaleOperator& so):_scale(so._scale) {}

  ScaleOperator& operator = (const ScaleOperator& so) { _scale = so._scale; return *this; }

  float _scale;

  inline void luminance(float& l) const { l*= _scale; }
  inline void alpha(float& a) const { a*= _scale; }
  inline void luminance_alpha(float& l,float& a) const { l*= _scale; a*= _scale;  }
  inline void rgb(float& r,float& g,float& b) const { r*= _scale; g*=_scale; b*=_scale; }
  inline void rgba(float& r,float& g,float& b,float& a) const { r*= _scale; g*=_scale; b*=_scale; a*=_scale; }
};
// ===============================================================
struct SubtractOperator
{
  SubtractOperator():_scale(1.0f) {}
  SubtractOperator(float scale):_scale(scale) {}
  SubtractOperator(const SubtractOperator& so):_scale(so._scale) {}

  SubtractOperator& operator = (const SubtractOperator& so) { _scale = so._scale; return *this; }

  float _scale;

  inline void luminance(float& l) const { l -= _scale; }
  inline void alpha(float& a) const { a -= _scale; }
  inline void luminance_alpha(float& l,float& a) const { l-= _scale; a-= _scale;  }
  inline void rgb(float& r,float& g,float& b) const { r-= _scale; g-=_scale; b-=_scale; }
  inline void rgba(float& r,float& g,float& b,float& a) const { r-= _scale; g-=_scale; b-=_scale; a-=_scale; }
};
//============================================================================
Image* RawManager::LoadRawFile(const char* path, int skip, int numBytes, 
                               int inX, int inY, int inZ,
                               int outX, int outY, int outZ,
                               int offX, int offY, int offZ)
{
  FS();
  
  long int fileSize = Helper::GetFileSize(path);
  long int paramSize = inX*inY*inZ*numBytes + skip;
  if(fileSize != paramSize)
  {
    Logger::Log("Given parameters don't match file size!");
    Logger::Log("Filesize       ", fileSize);
    Logger::Log("Calculated size ", paramSize);
    Logger::Log("Difference     ", fileSize - paramSize);
    FE();
    return 0;
  }
  
  if(outX+offX > inX || outY+offY > inY || outZ+offZ > inZ)
  {
    Logger::Log("Selected subvolume is out of bounds!");
    FE();
    return 0;
  }

  Logger::Log("Source file", path);
  Logger::Log("Source size", inX, inY, inZ);
  Logger::Log("Output size", outX, outY, outZ);
  Logger::Log("Offset size", offX, offY, offZ);
  
  osgDB::ifstream fin(path, ifstream::binary);
  if (!fin) 
  {
    Logger::Log("Unable to open file!");
    FE();
    return 0;
  }
  
  GLenum pixelFormat = GL_LUMINANCE;

  // number of bytes per component
  GLenum dataType = GL_UNSIGNED_BYTE;
  switch (numBytes)
  {
  case 1 : 
    dataType = GL_UNSIGNED_BYTE;	
    break;
  case 2 : 
    dataType = GL_UNSIGNED_SHORT;	
    break;
  }

  // allocate result image
  ref_ptr<Image> image = new Image;
  image->allocateImage(outX, outY, outZ, pixelFormat, dataType);
  if(!image->valid()) 
  {
    Logger::Log("Image allocation failed");  
    FE();
    return 0;
  }
  // skip header bytes, if any
  fin.seekg(skip, ios_base::cur);

  // get width and height differences
  long int dx = (inX - outX) * numBytes;
  long int dy = (inY - outY) * numBytes;

  // skip initial offset bytes, if any
  fin.seekg((inY * inX) * offZ * numBytes + 
            (inX * offY) * numBytes + 
             offX * numBytes, ios_base::cur);

  // extract 
  for(long int z = 0; z < outZ; z++)
  {
    if(z % (outZ / 10) == 0) 
      Logger::Log("Reading slice", z);

    for(long int y = 0; y < outY; y++)
    {
      char* data = (char*) image->data(0, y, z);
      for(long int x = 0; x < outX; x++)
      {
        if(fin.fail())
        {
          Logger::Log("Fail bit found");
          fin.clear();
          data++;
        }
        else
        {
          char* ptr = data;
          for(int b = 0; b < numBytes; ++b)
          {
            fin.read((char*)ptr, 1);
            ptr += 1;
          }
          data += numBytes;
        }
      }
      // skip remaining bytes
      fin.seekg(dx, ios_base::cur);
    }
    // skip remaining bytes
    fin.seekg((dy * inX), ios_base::cur);
  }

  // compute range of values
  osg::Vec4 minValue, maxValue;
  osg::computeMinMax(image.get(), minValue, maxValue);

  int mult =  256 << (8 * (numBytes - 1));

  Logger::Log("Max Intensity", maxValue.r() * mult);
  Logger::Log("Min Intensity", minValue.r() * mult);
  Logger::Log("Normalize texture");
  Logger::Log("Subt", minValue.r());
  Logger::Log("Mult", 1.0f / maxValue.r());

  //osg::modifyImage(image.get(), SubtractOperator(minValue.r()));
  //osg::modifyImage(image.get(), ScaleOperator(1.0f / maxValue.r()));

  FE();
  // done
  return image.release();
}
//============================================================================
bool LoadRawFile(const char* path, int skip, int numBytes, 
                  int inX, int inY, int inZ,
                  int outX, int outY, int outZ,
                  int offX, int offY, int offZ, char* dst)
{
  FILE* file = fopen(path, "r");
  long int fileSize = 0;
  if(file)
  {
    _fseeki64(file, 0, SEEK_END);
    fileSize = _ftelli64(file);
    fclose(file);
  }
  long int calcSize = inX * inY * inZ * numBytes + skip;
  if(fileSize != calcSize)
  {
    return false;
  }

  if(outX + offX > inX || 
     outY + offY > inY || 
     outZ + offZ > inZ)
  {
    return false;
  }

  std::ifstream fin(path, ifstream::binary);
  if (!fin) 
  {
    return false;
  }

  // skip header bytes, if any
  fin.seekg(skip, ios_base::cur);

  // get width and height deltas
  long int dx = (inX - outX) * numBytes;
  long int dy = (inY - outY) * numBytes;

  // skip initial offset bytes, if any
  fin.seekg((inY * inX) * offZ * numBytes + 
            (inX * offY) * numBytes + 
            offX * numBytes, ios_base::cur);
  
  // extract 
  for(long int z = 0; z < outZ; z++)
  {
    for(long int y = 0; y < outY; y++)
    {
      char* data = (char*) dst;
      for(long int x = 0; x < outX; x++)
      {
        if(fin.fail())
        {
          fin.clear();
          data++;
        }
        else
        {
          char* ptr = dst;
          for(int b = 0; b < numBytes; ++b)
          {
            fin.read((char*)ptr, 1);
            ptr += 1;
          }
          data += numBytes;
        }
      }
      // skip remaining bytes
      fin.seekg(dx, ios_base::cur);
    }
    // skip remaining bytes
    fin.seekg((dy * inX), ios_base::cur);
  }
  return true;
}

//============================================================================
void RawManager::Save( osg::Image* srcImg, const char* path )
{
  FS();

  // !!MUI IMPORTANTE!!
  // this function was "hacked" to 8 bit only for the unterhaching export.
  // might not work as expected anymore and needs to be fixed.
  // 

  FILE* outfile;
  outfile = fopen(path, "wb");
  if(outfile == 0)
  {
    Logger::Log("Cannot open output file");
    return;
  }

  int xs, ys, zs, size;
  xs = srcImg->s();
  ys = srcImg->t();
  zs = srcImg->r();
  
  int numBytes = 1;
  switch (srcImg->getDataType())
  {
  case GL_UNSIGNED_BYTE : numBytes = 1;	
    break;
  case GL_UNSIGNED_SHORT : numBytes = 2;	
    break;
  }
  
  // convert to 8 bit unsigned char
  osg::Image* resImg = new osg::Image;
  resImg->allocateImage(xs, ys, zs, GL_LUMINANCE, GL_UNSIGNED_BYTE);

  Logger::Log("exporting", xs, ys, zs, numBytes);

  for (int x = 0; x < xs; x++)
  {
    for (int y = 0; y < ys; y++)
    {
      for (int z = 0; z < zs; z++)
      {

        ushort* srcVal = (ushort*)srcImg->data(x, y, z);
        ushort val = srcVal[0];

        resImg->data(x, y, z)[0] = (val / 255);
      }
    }
  }

  size = xs * ys * zs * 1;

  Logger::Log("writing to disc");

  uchar* data = (uchar*)resImg->data(0, 0, 0);
  fwrite(data, 1, size, outfile);

  FE();
}
