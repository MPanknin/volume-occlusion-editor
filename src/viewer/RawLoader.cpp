#include <windows.h>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/fstream>
#include <osg/Image>
#include <osg/ImageUtils>

#include "RawLoader.h"
#include "Logger.h"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

using namespace osg;
using namespace std;

//============================================================================
Image* RawLoader::LoadRawFile(const char* path, int skip, int numBytes, 
                              int inX, int inY, int inZ,
                              int outX, int outY, int outZ,
                              int offX, int offY, int offZ)
{
  Logger::Log("Input dimension", inX, inY, inZ);
  Logger::Log("Output dimension ", outX, outY, outZ);

  osgDB::ifstream fin(path, ifstream::binary);
  if (!fin) return 0;

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
  if(!image->valid()) Logger::Log("image allocation failed");  

  // skip header bytes, if any
  fin.seekg(skip, ios_base::cur);

  // get width and height differences
  int dx = (inX - outX) * numBytes;
  int dy = (inY - outY) * numBytes;

  // skip initial offset bytes, if any
  fin.seekg((inY * inX) * offZ * numBytes + 
    (inX * offY) * numBytes + 
    offX * numBytes, ios_base::cur);

  uint maxIntensity = 0;

  // extract 
  for(int z = 0; z < outZ; z++)
  {
    if(z % (outZ / 10) == 0) 
      Logger::Log("Reading slice", z);

    for(int y = 0; y < outY; y++)
    {
      char* data = (char*) image->data(0, y, z);
      for(int x = 0; x < outX; x++)
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

  Logger::Log("Max Intensity", (int)maxIntensity);

  // done
  return image.release();
}