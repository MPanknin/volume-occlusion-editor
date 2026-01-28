#include <windows.h>

#include <driver_functions.h>

#include "osgDB\ReadFile"
#include "osgDB\WriteFile"
#include "osg\Image"
#include "osg\TransferFunction"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

using namespace osg;
using namespace std;

//#define BIT_16
#ifdef BIT_16
  #define TYPE ushort
  #define MULT 65536
#else
  #define TYPE uchar
  #define MULT 256
#endif

//=========================================================================================
// wrapper functions
extern "C"
void bindParams(const bool mapping, const float inc,
                const float scale, const float offset,
                const float x1, const float x2, 
                const float y1, const float y2);
extern "C"
void bindMappingLoookup(const bool useMapping, 
const float* vis);

extern "C" void 
bindVolume(const TYPE* h_vol, cudaExtent vd);

extern "C" void
kernel(TYPE* h_out, cudaExtent vd, const int radius, const float occScale);

//=========================================================================================
// entry point
int main(int argc, char* argv[])
{
  // size of filter mask
  ArgumentParser parser(&argc, argv);
  string infile;
  string outfile;
  int   rad = 0;
  float scale = 1.0f;

  parser.read("-in", infile);
  parser.read("-out", outfile);
  parser.read("-rad", rad);
  parser.read("-scale", scale);
  
  Image* inImg = osgDB::readImageFile(infile);
  int xs = inImg->s();
  int ys = inImg->t();
  int zs = inImg->r();
  cudaExtent vd = make_cudaExtent(xs, ys, zs);

  // the result image
  Image* outImg = new Image;
  outImg->allocateImage(xs, ys, zs, GL_LUMINANCE, inImg->getDataType());
  
  // 
  // setup the vis mapping
  TransferFunction1D* transfer = new TransferFunction1D;
  transfer->allocate(MULT);
  transfer->clear();

  string line;
  float intensity;
  float col;
  ifstream visin ("temp/vis.cfg");

  if (visin.is_open())
  {
    int lineCount = 0;
    while (visin.good())
    {
      getline (visin, line);
      if(line.find("point(") != -1)
      {
        int s = line.find("point(") + 6;
        int e = line.find(";");
        intensity = atof(line.substr(s, e - s).c_str());
        //printf("%f \n", intensity); 

        s = e + 1;
        e = line.find(")");
        col = atof(line.substr(s, e - s).c_str());
        transfer->setColor(intensity * MULT, Vec4(col, col, col, col));
      }
    }
  }
  else
  {
    printf("No visibility mapping found!!\n");
    return 0;  
  }
  float* vis = new float[MULT];
  for(int i = 0; i < MULT; i++)
  {
    vis[i] = transfer->getColor(i).x() * MULT;
    //printf("%f \n", vis[i]);
  }
  
  ////
  //// setup distance lookup
  //Image* distLookup = new Image;
  //int dlen = 2 * rad + 1;
  //distLookup->allocateImage(dlen, dlen, 1, GL_LUMINANCE, GL_UNSIGNED_BYTE);
  //
  //for (int x = -rad; x <= rad; x++)
  //{
  //  for (int y = -rad; y <= rad; y++)
  //  {
  //    Vec3 tmp(x, y, rad);
  //    float dst = (Vec3(0, 0, 0) - tmp).length();
  //    distLookup->data(x + rad, y + rad)[0] = (unsigned char)dst;
  //  }
  //}
  //
  //osgDB::writeImageFile(*distLookup, "temp/distLookup.bmp");

  bindMappingLoookup(true, vis);

  // bind volume to texture
  bindVolume((TYPE*)inImg->data(), vd);


  Timer timer;
  timer.setStartTick();

  // call wrapper
  kernel((TYPE*)outImg->data(), vd, rad, scale);
  
  double dt = timer.time_s();
  printf("%f \n", (float)dt);
  printf("%I \n", 999);

  std::ofstream file ("temp/test/cached_gpu.txt", std::ios::app);
  file << infile.c_str() << " | radius: " << rad << " | duration: " << (float)dt << " | samples:" << 1;
  file << "\n";
  file.close();


  //// building result volume
  //int numBytes;

  //// number of bytes per component
  //switch (inImg->getDataType())
  //{
  //case GL_UNSIGNED_BYTE : numBytes = 1;	
  //  break;
  //case GL_UNSIGNED_SHORT : numBytes = 2;	
  //  break;
  //}

  //Image* temp = new Image;
  //temp->allocateImage(xs, ys, zs, GL_LUMINANCE_ALPHA, inImg->getDataType());
  //
  //printf("----\n");
  //printf("Building result volume\n");

  //uchar* data = (uchar*)temp->data(0, 0, 0);
  //uchar* src  = (uchar*)inImg->data(0, 0, 0);
  //uchar* occ  = (uchar*)outImg->data(0, 0, 0);

  //for(int z = 0; z < zs; z++)
  //{
  //  for(int y = 0; y < ys; y++)
  //  {
  //    for(int x = 0; x < xs; x++)
  //    {
  //      if (numBytes == 1)
  //      {
  //        data[0] = *src++;
  //        data[1] = *occ++;
  //        data += 2; 
  //      } 
  //      else if(numBytes == 2)
  //      {
  //        data[0] = *src++;
  //        data[1] = *src++;
  //        data[2] = *occ++;
  //        data[3] = *occ++;
  //        data += 4; 
  //      }
  //    }
  //  }
  //}

  //// save the filtered image
  //osgDB::writeImageFile(*temp, outfile.c_str());

  // thats it. were done
  return EXIT_SUCCESS;
}
