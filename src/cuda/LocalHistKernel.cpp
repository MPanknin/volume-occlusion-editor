//#include <windows.h>
//
//#include <driver_functions.h>
//
//#include "osgDB\ReadFile"
//#include "osgDB\WriteFile"
//#include "osg\Image"
//#include "osg\TransferFunction"
//
//typedef unsigned int uint;
//typedef unsigned char uchar;
//typedef unsigned short ushort;
//
//using namespace osg;
//using namespace std;
//
//#define TYPE uchar
//#define MULT 256
//
//const int numBins = 10;
//
////=========================================================================================
//// wrapper functions
//extern "C"
//void bindParams(const bool mapping, const float inc,
//                const float scale, const float offset,
//                const float x1, const float x2, 
//                const float y1, const float y2);
//extern "C"
//void bindMappingLoookup(const bool useMapping, 
//const float* vis);
//
//extern "C" void 
//bindVolume(const TYPE* h_vol, cudaExtent vd);
//
//extern "C" void
//kernel(TYPE* h_out, cudaExtent vd, const int radius, const float occScale);
//
////=========================================================================================
//// entry point
//int main(int argc, char* argv[])
//{
//  // size of filter mask
//  ArgumentParser parser(&argc, argv);
//  string infile;
//  string outfile;
//  int   rad = 0;
//
//  parser.read("-in", infile);
//  parser.read("-out", outfile);
//  parser.read("-rad", rad);
//  
//  Image* inImg = osgDB::readImageFile(infile);
//  int xs = inImg->s();
//  int ys = inImg->t();
//  int zs = inImg->r();
//  cudaExtent vd = make_cudaExtent(xs, ys, zs);
//
//  // bind volume to texture
//  bindVolume((TYPE*)inImg->data(), vd);
//
//  // launch kernel
//  const int size = xs * ys * zs * numBins;
//  uchar* histBuffer = new uchar[size];
//  kernel(histBuffer, vd, rad, 1);
//  
//  printf("----\n");
//  printf("Building result volume\n");
//
//  int samplesTaken = 0;
//
//  //HistogramCollection collection(numBins);
//  //collection.SrcX(xs);
//  //collection.SrcY(ys);
//  //collection.SrcZ(zs);
//
//  for(int z = 0; z < zs; z++)
//  {
//    for(int y = 0; y < ys; y++)
//    {
//      for(int x = 0; x < xs; x++)
//      {
//        samplesTaken++;
//        //Histogram* tmp = collection.CreateHistogram();
//        //tmp->SetIntensity((int)inImg->data(x, y, z)[0]);
//        //tmp->SetOrigin(x, y, z);
//
//        //for (int i = 0; i < numBins; i++)
//        //{
//        //  tmp->SetBinValue(i, (int)*histBuffer++);
//        //}
//      }
//    }
//  }
//
//  printf("Num voxels in interval: %i \n", samplesTaken);
//
//  //std::ofstream file;
//  //file.open(outfile.c_str());
//  //file << collection;
//  //file.close();
//
//  system("pause");
//
//  // thats it. were done
//  return EXIT_SUCCESS;
//}

/*
#include <windows.h>

#include <driver_functions.h>

#include "osgDB\ReadFile"
#include "osgDB\WriteFile"
#include "osg\Image"
#include "osg\TransferFunction"
#include "..\viewer\Logger.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

using namespace osg;
using namespace std;

#define TYPE uchar
#define MULT 256

const int numBins = 10;

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

parser.read("-inFile", infile);
parser.read("-radius", rad);

Image* inImg = osgDB::readImageFile(infile);
int xs = inImg->s();
int ys = inImg->t();
int zs = inImg->r();
cudaExtent vd = make_cudaExtent(xs, ys, zs);

Image* outImg = new Image;
outImg->allocateImage(xs, ys, zs, GL_LUMINANCE, inImg->getDataType());

// bind volume to texture
bindVolume((TYPE*)inImg->data(), vd);


Timer timer;
timer.setStartTick();

// launch kernel
kernel((uchar*)outImg->data(), vd, rad, 1);

double dt = timer.time_s();

printf("%f \n", (float)dt);
printf("%I \n", 999);

//Logger::Log("Duration in ms:", (float)dt);
//Logger::Log("Samples taken:", (unsigned long long int)999);

std::ofstream file ("temp/test/bruteforce_gpu.txt", std::ios::app);
file << infile.c_str() << " | radius: " << rad << " | duration: " << (float)dt << " | samples:" << 1;
file << "\n";
file.close();


//printf("----\n");
//printf("Building result volume\n");

//Image* temp = new Image;
//temp->allocateImage(xs, ys, zs, GL_LUMINANCE_ALPHA, inImg->getDataType());

//int samplesTaken = 0;

//uchar* data = (uchar*)temp->data(0, 0, 0);
//uchar* src  = (uchar*)inImg->data(0, 0, 0);
//uchar* occ  = (uchar*)outImg->data(0, 0, 0);

//for(int z = 0; z < zs; z++)
//{
//  for(int y = 0; y < ys; y++)
//  {
//    for(int x = 0; x < xs; x++)
//    {
//      data[0] = *src++;
//      data[1] = *occ++;
//      data += 2; 
//    }
//  }
//}
//
//// save the filtered image
//osgDB::writeImageFile(*temp, outfile.c_str());

//system("pause");

// thats it. were done
return EXIT_SUCCESS;
}


*/
