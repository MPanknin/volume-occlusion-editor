//#include <iosfwd>
//
//#include "osg/ArgumentParser"
//#include "osg/TransferFunction"
//
//#include "osgDB/WriteFile"
//#include "osgDB/ReadFile"
//
//#include "ApplicationPaths.h"
//#include "Helper.h"
//#include "Histogram.h"
//#include "HistogramCollection.h"
//#include "Logger.h"
//#include "MappingBasic.h"
//#include "MappingLinear.h"
//#include "MappingSeismicRamp.h"
//#include "VisibilityMapper.h"
//#include "VolumeManager.h"
//
//using namespace osg;
////============================================================================
//bool Inside(Image* img, Vec3f p)
//{
//  if(p.x() >= 0 && p.x() < img->s() &&
//     p.y() >= 0 && p.y() < img->t() &&
//     p.z() >= 0 && p.z() < img->r())
//  {
//    return true;
//  }
//  return false;
//}
//
////============================================================================
//int GetVoxel(Image* img, Vec3f pos)
//{
//  if(Inside(img, pos)) // sanity check
//  {
//    int res = img->data(pos.x(), pos.y(), pos.z())[0];
//    return res;
//  }
//  return 0;
//}
//
////============================================================================
//
//unsigned long long int totalSamples = 0;
//
////============================================================================
//uchar cache[2000][2000];
//
////============================================================================
//uchar GradientMagnitude(Image* volImg, int x, int y, int z)
//{
//  Vec3 pos(x, y, z);
//
//  Vec3f sample1;
//  Vec3f sample2;
//  Vec3f grad;
//
//  int DX = 1;
//  int DY = 1;
//  int DZ = 1;
//
//  sample1.x() = GetVoxel(volImg, pos - Vec3(DX, 0, 0));
//  sample2.x() = GetVoxel(volImg, pos + Vec3(DX, 0, 0));
//
//  sample1.y() = GetVoxel(volImg, pos - Vec3(0, DY, 0));
//  sample2.y() = GetVoxel(volImg, pos + Vec3(0, DY, 0));
//
//  sample1.z() = GetVoxel(volImg, pos - Vec3(0, 0, DZ));
//  sample2.z() = GetVoxel(volImg, pos + Vec3(0, 0, DZ));
//
//  grad = sample1 - sample2;
//
//  return grad.length();
//}
////============================================================================
//uchar OcclusionCached(Image* volImg, int x, int y, int z, int rad)
//{
//  Vec3 pos(x, y, z);
//
//  float s = 2 * rad + 1;
//  float w = s * s * s;
//
//  volImg->data(x, y, z)[0] = 250;
//
//  int inX = volImg->s();
//  int inY = volImg->t();
//  int inZ = volImg->r();
//
//  float add = 0;
//  float subt = 0;
//
//  {
//    // start and end voxel
//    Vec3 minVec = pos - Vec3(rad, rad, rad);
//    Vec3 maxVec = pos + Vec3(-rad, rad, rad);
//
//    int minX = minVec.x();
//    int minY = minVec.y();
//    int minZ = minVec.z();
//
//    int maxX = maxVec.x();
//    int maxY = maxVec.y();
//    int maxZ = maxVec.z();
//
//    minX = std::max(minX, 0);
//    minY = std::max(minY, 0);
//    minZ = std::max(minZ, 0);
//
//    maxX = std::min(maxX, inX);
//    maxY = std::min(maxY, inY);
//    maxZ = std::min(maxZ, inZ);
//
//    int lenX = (maxX - minX);
//    int lenY = (maxY - minY);
//    int lenZ = (maxZ - minZ);
//
//    int dx = (inX - lenX) - 1;
//    int dy = (inY - lenY) - 1;
//
//    int firstByte = (inY * inX) * minZ + (inX * minY) + minX; 
//    uchar* data = volImg->data(firstByte);
//
//    // sample image and fill bins
//    for (int z = 0; z < lenZ; z++)
//    {
//      for (int y = 0; y < lenY; y++)
//      {
//        for (int x = 0; x < lenX + 1; x++)
//        {
//          add += *data;
//          data++;
//          totalSamples++;
//        }
//        data += dx;
//      }
//      data += dy * inX;
//    }
//  }
//
//  {
//    // start and end voxel
//    Vec3 minVec = pos - Vec3(-rad, rad, rad);
//    Vec3 maxVec = pos + Vec3(rad, rad, rad);
//
//    int minX = minVec.x();
//    int minY = minVec.y();
//    int minZ = minVec.z();
//
//    int maxX = maxVec.x();
//    int maxY = maxVec.y();
//    int maxZ = maxVec.z();
//
//    minX = std::max(minX, 0);
//    minY = std::max(minY, 0);
//    minZ = std::max(minZ, 0);
//
//    maxX = std::min(maxX, inX);
//    maxY = std::min(maxY, inY);
//    maxZ = std::min(maxZ, inZ);
//
//    int lenX = maxX - minX;
//    int lenY = maxY - minY;
//    int lenZ = maxZ - minZ;
//
//    int dx = (inX - lenX) - 1;
//    int dy = (inY - lenY) - 1;
//
//    int firstByte = (inY * inX) * minZ + (inX * minY) + minX; 
//    uchar* data = volImg->data(firstByte);
//
//    // sample image and fill bins
//    for (int z = 0; z < lenZ; z++)
//    {
//      for (int y = 0; y < lenY; y++)
//      {
//        for (int x = 0; x < lenX + 1; x++)
//        {
//          subt += *data;
//          data++;
//          totalSamples++;
//        }
//        data += dx;
//      }
//      data += dy * inX;
//    }
//  }
//
//  float diff = (add - subt) / w;
//
//  float occ = diff + cache[x][y];
//  cache[x][y] = occ;
//
//  return (uchar)occ;
//}
//
////============================================================================
//uchar OcclusionPlain(Image* volImg, int x, int y, int z, int rad)
//{
//  Vec3 pos(x, y, z);
//
//  int inX = volImg->s();
//  int inY = volImg->t();
//  int inZ = volImg->r();
//
//  // start and end voxel
//  Vec3 minVec = pos - Vec3(rad, rad, rad);
//  Vec3 maxVec = pos + Vec3(rad, rad, rad);
//
//  int res = 0;
//  int samplesTaken = 0;
//
//  int minX = minVec.x();
//  int minY = minVec.y();
//  int minZ = minVec.z();
//
//  int maxX = maxVec.x();
//  int maxY = maxVec.y();
//  int maxZ = maxVec.z();
//
//  minX = std::max(minX, 0);
//  minY = std::max(minY, 0);
//  minZ = std::max(minZ, 0);
//
//  maxX = std::min(maxX, inX);
//  maxY = std::min(maxY, inY);
//  maxZ = std::min(maxZ, inZ);
//
//  int lenX = maxX - minX;
//  int lenY = maxY - minY;
//  int lenZ = maxZ - minZ;
//
//  int dx = (inX - lenX) - 1;
//  int dy = (inY - lenY) - 1;
//
//  int firstByte = (inY * inX) * minZ + (inX * minY) + minX; 
//  uchar* data = volImg->data(firstByte);
//
//  // intensity value for this voxel
//  int voxel = (int)GetVoxel(volImg, pos);
//
//  // sample image and fill bins
//  for (int z = 0; z < lenZ; z++)
//  {
//    for (int y = 0; y < lenY; y++)
//    {
//      for (int x = 0; x < lenX; x++)
//      {
//        uchar val = *data;
//        data++;
//        res += val;
//        samplesTaken++;
//        totalSamples++;
//      }
//      data += dx;
//    }
//    data += dy * inX;
//  }
//
//  res /= samplesTaken;
//
//  return (uchar)res;
//}
//
////============================================================================
//float euclideanLen(Vec4f a, Vec4f b, float d)
//{
//  float mod = (b.x() - a.x()) * (b.x() - a.x()) +
//              (b.y() - a.y()) * (b.y() - a.y()) +
//              (b.z() - a.z()) * (b.z() - a.z()) +
//              (b.w() - a.w()) * (b.w() - a.w());
//
//  return expf(-mod / (2 * d * d));
//}
//
////============================================================================
//uchar OccBilateral(Image* volImg, float* gaussian, int x, int y, int z, int rad)
//{
//  Vec3 pos(x, y, z);
//
//  int inX = volImg->s();
//  int inY = volImg->t();
//  int inZ = volImg->r();
//
//  // start and end voxel
//  Vec3 minVec = pos - Vec3(rad, rad, rad);
//  Vec3 maxVec = pos + Vec3(rad, rad, rad);
//
//  int minX = minVec.x();
//  int minY = minVec.y();
//  int minZ = minVec.z();
//
//  int maxX = maxVec.x();
//  int maxY = maxVec.y();
//  int maxZ = maxVec.z();
//
//  minX = std::max(minX, 0);
//  minY = std::max(minY, 0);
//  minZ = std::max(minZ, 0);
//
//  maxX = std::min(maxX, inX);
//  maxY = std::min(maxY, inY);
//  maxZ = std::min(maxZ, inZ);
//
//  int lenX = maxX - minX;
//  int lenY = maxY - minY;
//  int lenZ = maxZ - minZ;
//
//  int dx = (inX - lenX);
//  int dy = (inY - lenY);
//
//  int firstByte = (inY * inX) * minZ + (inX * minY) + minX; 
//  uchar* data = volImg->data(firstByte);
//
//  // intensity value for this voxel
//  float voxel = (float)GetVoxel(volImg, pos);
//
//  float factor;
//  float sum = 0;
//  float t = 0.0f;
//  int samplesTaken = 0;
//
//  // sample image and fill bins
//  for (int z = 0; z < lenZ; z++)
//  {
//    for (int y = 0; y < lenY; y++)
//    {
//      for (int x = 0; x < lenX; x++)
//      {
//        float curPix = (float)(*data);
//        data++;
//        factor = gaussian[x] * gaussian[y] * gaussian[z];
//
//        Vec4f a(voxel, voxel, voxel, voxel);
//        Vec4f b(curPix, curPix, curPix, curPix);
//
//        float dist = euclideanLen(a, b, 0.1f);
//
//        factor *= dist;
//        
//        //printf("%f \n", dist);
//
//        t += curPix * factor;
//        sum += factor;
//
//        totalSamples++;
//      }
//      data += dx;
//    }
//    data += dy * inX;
//  }
//
//  t /= sum;
//
//  return (uchar)t;
//}
//
////============================================================================
//int main(int argc, char* argv[])
//{
//  Logger::SetLevel(Logger::TRACE);
//
//  ArgumentParser parser(&argc, argv);
//  std::string inFile = "";
//  parser.read("-inFile", inFile);
//
//  int radius = 5;
//  parser.read("-radius", radius);
//
//  const int size = 2 * radius + 1;
//  float* gaussian = new float[size];
//
//  float delta = 4.0f;
//
//  for (int x = -radius; x <= radius; x++)
//  {
//    gaussian[x + radius] = expf(-(x * x) / (2 * delta * delta));
//    //printf("%f ", gaussian[x + radius]);
//  }
//  //printf("\n");
//
//  Image* volImg = osgDB::readImageFile(inFile.c_str());
//
//  int xs = volImg->s();
//  int ys = volImg->t();
//  int zs = volImg->r();
//
//  Image* resImg = new Image;
//  resImg->allocateImage(xs, ys, zs, GL_LUMINANCE_ALPHA, volImg->getDataType());
//    
//  uchar* data = (uchar*)resImg->data(0, 0, 0);
//  uchar* src  = (uchar*)volImg->data(0, 0, 0);
//
//  Timer timer;
//  timer.setStartTick();
//
//  //OccBilateral(volImg, gaussian, 11, 11, 11, radius);
//
//  for(int z = 0; z < zs; z++)
//  {
//    //if(z % 10 == 0) 
//    //  Logger::Log("", z);
//
//    for(int y = 0; y < ys; y++)
//    {
//      for(int x = 0; x < xs; x++)
//      {
//        data[0] = *src++;
//        //data[1] = OccBilateral(volImg, gaussian, x, y, z, radius);
//        data[1] = OcclusionCached(volImg, x, y, z, radius);
//        data += 2; 
//      }
//    }
//  }  
//
//  double dt = timer.time_s();
//  Logger::Log("Duration in ms:", (float)dt);
//  Logger::Log("Samples taken:", totalSamples);
//
//  std::ofstream file ("temp/test/cached_cpu.txt", std::ios::app);
//  file << inFile.c_str() << " | radius: " << radius << " | duration: " << (float)dt << " | samples:" << totalSamples;
//  file << "\n";
//  file.close();
//
//  //Image* hist = Helper::CreateCrossPlot(resImg);
//  //osgDB::writeImageFile(*hist, OCC_SPECTRUM);
//  //osgDB::writeImageFile(*resImg, VOL_IMAGE);
//
//  //system("pause");
//
//  return 1;
//}
//
//
