#include <osg/StateSet>
#include <osg/Node>
#include <osg/Image>

#include "osgDB/Output"
#include "osgDB/WriteFile"

#include "Helper.h"
#include "Logger.h"
#include "osg/Vec2"
#include "HistogramCollection.h"
#include <assert.h>

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;

//============================================================================
void Helper::SetDrawMode( osg::Node* srcNode, osg::PolygonMode::Mode mode )
{
  if( srcNode == NULL )
    return;
  osg::StateSet* state = srcNode->getOrCreateStateSet();
  osg::PolygonMode* polyModeObj;

  polyModeObj = dynamic_cast< osg::PolygonMode* >
    ( state->getAttribute( osg::StateAttribute::POLYGONMODE ));

  if ( !polyModeObj ) 
  {
    polyModeObj = new osg::PolygonMode;
    state->setAttribute( polyModeObj );    
  }
  polyModeObj->setMode(osg::PolygonMode::FRONT_AND_BACK, mode);
}
//============================================================================
bool Helper::PointInPoly( int nvert, float* vertx, float* verty, float testx, float testy )
{
  int i, j;
  bool c = false;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
      (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
      c = !c;
  }
  return c;
}

//============================================================================
struct HistRes
{
  int minVal;
  int maxVal;

  double sum;
  double mean;
  double variance;

  void print()
  {

  }
};
//============================================================================
void Helper::FillHistogram(osg::Image* inImg, osg::Vec3 voxel, int rad, Histogram* histogram )
{
  using namespace osg;

  // get source dimensions
  int inX = inImg->s();
  int inY = inImg->t();
  int inZ = inImg->r();

  // start and end voxel
  Vec3 minVec = voxel - Vec3(rad, rad, rad);
  Vec3 maxVec = voxel + Vec3(rad, rad, rad);

  int minX = minVec.x();
  int minY = minVec.y();
  int minZ = minVec.z();

  int maxX = maxVec.x();
  int maxY = maxVec.y();
  int maxZ = maxVec.z();

  minX = std::max(minX, 0);
  minY = std::max(minY, 0);
  minZ = std::max(minZ, 0);

  maxX = std::min(maxX, inX);
  maxY = std::min(maxY, inY);
  maxZ = std::min(maxZ, inZ);

  int lenX = maxX - minX;
  int lenY = maxY - minY;
  int lenZ = maxZ - minZ;

  //Logger::Log("max", maxX, maxY, maxZ);
  //Logger::Log("min", minX, minY, minZ);

  // width and height deltas
  int dx = (inX - lenX) - 1;
  int dy = (inY - lenY) - 1;

  int firstByte = (inY * inX) * minZ + (inX * minY) + minX; 
  uchar* data = inImg->data(firstByte);

  // sample image and fill bins
  for (int z = 0; z < lenZ; z++)
  {
    for (int y = 0; y < lenY; y++)
    {
      for (int x = 0; x < lenX; x++)
      {
        uchar val = *data;
        histogram->AddValue(val);
        data++;
      }
      data += dx;
    }
    data += dy * inX;
  }
}

//============================================================================
void Helper::CreateLocalHistogram( osg::Image* inImg, int rad, int minVal, int maxVal, HistogramCollection& histCollection )
{
  FS();

  int xs = inImg->s();
  int ys = inImg->t();
  int zs = inImg->r();

  int samplesTaken = 0;

  for(int z = 0; z < zs; z++)
  {
    if(z % 5 == 0) Logger::Log("", z);

    for(int y = 0; y < ys; y++)
    {
      for(int x = 0; x < xs; x++)
      {
        unsigned char data = *(inImg->data(x, y, z));
        if (data < minVal || data > maxVal)
        {
          continue;
        }
        else
        {
          samplesTaken++;
          Histogram* tmp = histCollection.CreateHistogram();

          FillHistogram(inImg, osg::Vec3(x, y, z), rad, tmp);

          tmp->SetIntensity(data);
          tmp->SetOrigin(x, y, z);
          tmp->Normalize();
          tmp->DeleteBinBuffer();
        }
      }
    }
  }

  Logger::Log("Num voxels in interval", samplesTaken);

  FE();
}

//============================================================================
osg::Image* Helper::CreateLocalHistogram(osg::Image* inImg, osg::Vec3f voxel, int rad, int outX, int outY)
{
  FS();
  
  using namespace osg;
  
  // num bins
  const int n = 256;

  // buffer for bins
  float res[n];

  // histogram image
  ref_ptr<Image> hist = new osg::Image;
  hist->allocateImage(256, 256, 1, GL_RGBA, GL_UNSIGNED_BYTE);
  
  // clear to white
  for(int x = 0; x < 256; x++)
  {
    for(int y = 0; y < 256; y++)
    {
      hist->data(x, y, 0)[0] = 255;
      hist->data(x, y, 0)[1] = 255;
      hist->data(x, y, 0)[2] = 255;
      hist->data(x, y, 0)[3] = 255;
    }
    res[x] = 0;
  }

  // get source dimensions
  int inX = inImg->s();
  int inY = inImg->t();
  int inZ = inImg->r();

  // start and end voxel
  Vec3 minVec = voxel - Vec3(rad, rad, rad);
  Vec3 maxVec = voxel + Vec3(rad, rad, rad);

  int minX = minVec.x();
  int minY = minVec.y();
  int minZ = minVec.z();

  int maxX = maxVec.x();
  int maxY = maxVec.y();
  int maxZ = maxVec.z();

  minX = std::max(minX, 0);
  minY = std::max(minY, 0);
  minZ = std::max(minZ, 0);

  maxX = std::min(maxX, inX);
  maxY = std::min(maxY, inY);
  maxZ = std::min(maxZ, inZ);

  int lenX = maxX - minX;
  int lenY = maxY - minY;
  int lenZ = maxZ - minZ;

  Logger::Log("max", maxX, maxY, maxZ);
  Logger::Log("min", minX, minY, minZ);

  // width and height deltas
  int dx = (inX - lenX);
  int dy = (inY - lenY);

  int firstByte = (inY * inX) * minZ + (inX * minY) + minX; 
  uchar* data = inImg->data(firstByte);

  float occ = 0;
  float numSamples = 0;

  // sample image and fill bins
  for (int z = 0; z < lenZ; z++)
  {
    for (int y = 0; y < lenY; y++)
    {
      for (int x = 0; x < lenX; x++)
      {
        uchar val = data[0];
        res[(int)val] += 1;
        occ += (float)val;
        numSamples++;
        data++;
      }
      data += dx;
    }
    data += dy * inX;
  }

  Logger::Log("occ", occ / (numSamples));

  // build histogram 
  // min / max from bins
  int maxVal = INT_MIN;
  int minVal = INT_MAX;
  
  float sum = 0;
  for(int x = 0; x < n; x++)
  {
    float c = res[x];
    maxVal = c > maxVal ? c: maxVal;
    minVal = c < minVal ? c: minVal;

    sum += c;
  }
  Logger::Log("bins min max", minVal, maxVal);
  
  // arithmetic mean 
  float mean = sum / n;
  Logger::Log("mean", mean);
  Logger::Log("centroid", (int)mean);
  
  // squared deviation from mean
  float squareDev = 0;
  for(int x = 0; x < n; x++)
  {
    squareDev += pow(res[x] - mean, 2);
  }

  // arithmetic mean of quadratic deviation
  float variance = squareDev / (n - 1);
  Logger::Log("variance", variance);

  // normalize
  for(int x = 0; x < n; x++)
  {
    res[x] -= minVal;
    res[x] *= (float)n / (float)maxVal;
  }

   //write bin values into image
  for(int x = 0; x < n; x++)
  {
    for(int y = 0; y < res[x] && y < n; y++)
    {
      hist->data(x, y, 0)[0] = 0;
      hist->data(x, y, 0)[1] = 0;
      hist->data(x, y, 0)[2] = 0;
    }
  }

  // highlight mean
  for(int y = 0; y < 256; y++)
  {
    hist->data(mean, y, 0)[0] = 0;
    hist->data(mean, y, 0)[1] = 0;
    hist->data(mean, y, 0)[2] = 0;
  }

  // scale it
  hist->scaleImage(outX, outY, 1, GL_UNSIGNED_BYTE);

  FE();
  return hist.release();

  //return 0;
}
//============================================================================
osg::Image* Helper::CreateLocalHistogram( osg::Image* inImg, int outX, int outY )
{
  FS();
  using namespace osg;

  int xs = inImg->s();
  int ys = inImg->t();
  int zs = inImg->r();

  Logger::Log("Dimensions", xs, ys, zs);

  // histogram image
  ref_ptr<Image> hist = new osg::Image;
  hist->allocateImage(256, 256, 1, GL_RGBA, GL_UNSIGNED_BYTE);

  // buffer for bins
  float res[256];

  // clear to white
  for(int x = 0; x < 256; x++)
  {
    for(int y = 0; y < 256; y++)
    {
      hist->data(x, y, 0)[0] = 255;
      hist->data(x, y, 0)[1] = 255;
      hist->data(x, y, 0)[2] = 255;
      hist->data(x, y, 0)[3] = 255;
    }
    res[x] = 0;
  }

  // number of bytes per component
  int numBytes = 1;
  switch (inImg->getDataType())
  {
  case GL_UNSIGNED_BYTE: 
    numBytes = 1;	
    break;
  case GL_UNSIGNED_SHORT: 
    numBytes = 2;	
    break;
  }

  Logger::Log("Bytes per voxel", numBytes);

  // extract 
  for(int z = 0; z < zs; z++)
  {
    for(int y = 0; y < ys; y++)
    {
      char* data = (char*) inImg->data(0, y, z);
      for(int x = 0; x < xs; x++)
      {
        if(numBytes == 1)
        {
          uchar* idx = (uchar*)data;

          int val = *idx;
          res[val] += 1;
        }
        else if(numBytes == 2)
        {
          ushort* idx = (ushort*)data;
          uint val = 0;
          val = *idx;
          res[val / 256] += 1;
        }
        data += numBytes;
      }
    }
  }

  // build histogram 
  // get min / max
  int maxVal = INT_MIN;
  int minVal = INT_MAX;

  for(int x = 0; x < 256; x++)
  {
    float c = res[x];
    maxVal = c > maxVal ? c: maxVal;
    minVal = c < minVal ? c: minVal;
  }

  // normalize
  for(int x = 0; x < 256; x++)
  {
    res[x] -= minVal;
    res[x] *= (float)256 / (float)maxVal;
  }

  // write into image
  for(int x = 0; x < 256; x++)
  {
    for(int y = 0; y < res[x] && y < 256; y++)
    {
      hist->data(x, y, 0)[0] = 0;
      hist->data(x, y, 0)[1] = 0;
      hist->data(x, y, 0)[2] = 0;
    }
  }

  // scale and save it
  hist->scaleImage(outX, outY, 1, GL_UNSIGNED_BYTE);

  FE();
  return hist.release();
}
//============================================================================

//============================================================================
osg::Image* Helper::CreateCrossPlot( osg::Image* vol )
{
  FS();

  int xs = vol->s();
  int ys = vol->t();
  int zs = vol->r();

  float resR[256][256];
  float resG[256][256];
  float resB[256][256];

  osg::Image* image = new osg::Image;
  image->allocateImage(256, 256, 1, GL_RGB, GL_UNSIGNED_BYTE);

  int numBytes = 1;
  switch (vol->getDataType())
  {
  case GL_UNSIGNED_BYTE:
    numBytes = 1;
    break;
  case GL_UNSIGNED_SHORT:
    numBytes = 2;
    break;
  }

  Logger::Log("Input dimensions", xs, ys, zs);
  Logger::Log("Bytes per voxel", numBytes);

  // reset image data
  for(int x = 0; x < 256; x++)
  {
    for(int y = 0; y < 256; y++)
    {
      image->data(x, y, 0)[0] = 255;
      image->data(x, y, 0)[1] = 255;
      image->data(x, y, 0)[2] = 255;
      resR[x][y] = 0;
      resG[x][y] = 0;
      resB[x][y] = 0;
    }
  }

  for(int x = 0; x < xs; x++)
  {
    for(int y = 0; y < ys; y++)
    {
      for(int z = 0; z < zs; z++)
      {
        if(numBytes == 1)
        {
          unsigned char i = vol->data(x, y, z)[0];
          unsigned char o = vol->data(x, y, z)[1];
          resR[(int)i][(int)o] += 1.0f;
        }
        else if(numBytes == 2)
        {
          unsigned short* data = (unsigned short*)vol->data(x, y, z);
          unsigned short i = data[0];
          unsigned short o = data[1];

          resR[(int)i / 256][(int)o / 256] += 1.0f;
        }
      }
    }
  }

  float max = (float)INT_MIN;
  float min = (float)INT_MAX;
  for(int x = 0; x < 256; x++)
  {
    for(int y = 0; y < 256; y++)
    {
      float c = resG[x][y];
      max = c > max ? c: max;
      min = c < min ? c: min;
    }
  }

  for(int x = 0; x < 256; x++)
  {
    for(int y = 0; y < 256; y++)
    {
      float valR = resR[x][y] > 255 ? 255: resR[x][y];

      image->data(x, y, 0)[0] = 255 - (unsigned char)valR;
      image->data(x, y, 0)[1] = 255 - (unsigned char)valR;
      image->data(x, y, 0)[2] = 255 - (unsigned char)valR;
    }
  }
  image->scaleImage(512, 512, 1, GL_UNSIGNED_BYTE);

  FE();
  return image;
}
//============================================================================
long int Helper::GetFileSize( const char* path )
{
  FILE* file = fopen(path, "r");
  long int size = 0;
  if(file)
  {
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
  }
  else
  {
    Logger::Log("Unable to open file");
  }
  return size;
}
//============================================================================
void Helper::SplitString( const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens )
{
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, lastPos);
  }
}

//============================================================================
#define PI 3.14159265358979323846

double Helper::RandomNormalDistribution(double mu, double sigma) 
{
  static bool deviateAvailable=false;	//	flag
  static float storedDeviate;			//	deviate from previous calculation
  double dist, angle;

  //	If no deviate has been stored, the standard Box-Muller transformation is 
  //	performed, producing two independent normally-distributed random
  //	deviates.  One is stored for the next round, and one is returned.
  if (!deviateAvailable) {

    //	choose a pair of uniformly distributed deviates, one for the
    //	distance and one for the angle, and perform transformations
    dist=sqrt( -2.0 * log(double(rand()) / double(RAND_MAX)) );
    angle=2.0 * PI * (double(rand()) / double(RAND_MAX));

    //	calculate and store first deviate and set flag
    storedDeviate=dist*cos(angle);
    deviateAvailable=true;

    //	calcaulate return second deviate
    return dist * sin(angle) * sigma + mu;
  }

  //	If a deviate is available from a previous call to this function, it is
  //	returned, and the flag is set to false.
  else {
    deviateAvailable=false;
    return storedDeviate*sigma + mu;
  }
}

