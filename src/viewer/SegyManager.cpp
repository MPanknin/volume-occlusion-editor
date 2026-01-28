#include <assert.h>

#include <osg\Image>

#include "SegyManager.h"
#include "Logger.h"
#include "Util.h"

//============================================================================
SegyManager::SegyManager()
{
  m_inFile = 0;
  m_min = 0;
}
//============================================================================
SegyManager::~SegyManager()
{
  if(m_inFile) 
  {
    fclose(m_inFile);
    m_inFile = 0;
  }
}
//============================================================================
bool SegyManager::Open(const char* filename)
{
  FS();
  if(m_inFile) 
  {
    fclose(m_inFile);
  }

  m_inFile = fopen(filename, "rb");
  m_timeOffset = 0;

  if(m_inFile)
  {
    // get total file size
    fseek(m_inFile, 0, SEEK_END);
    m_fileSize = ftell(m_inFile);
    fseek(m_inFile, 0, SEEK_SET);

    // read txt header
    fread(m_txtHdr, 1, 3200, m_inFile);

    // read binary header
    fread(m_binHdr, 1, 400, m_inFile);

    // sample interval in ms
    m_sampleInterval = i2(m_binHdr, 17);
    if(m_sampleInterval <= 0) 
    {
      Logger::Log("Sample interval is negative!", m_sampleInterval);
      fclose(m_inFile); m_inFile = 0; 
      return false;
    }
    
    // samples per data trace
    m_numSamples = i2(m_binHdr, 21); 
    if(m_numSamples <= 0)
    {
      Logger::Log("Num samples per data trace is negative!", m_numSamples);
      fclose(m_inFile); m_inFile = 0; 
      return false;
    }

    // data sample format code
    m_format = i2(m_binHdr, 25); 
    if(m_format < 1 || m_format > 8) 
    {
      Logger::Log("Unknown format code", m_format);
      fclose(m_inFile); m_inFile = 0; 
      return false;
    }

    // get number of bytes per voxel
    if (m_format == 3) 
    {
      m_bytesPerVoxel = 2;
    }
    else if(m_format == 8) 
    {
      m_bytesPerVoxel = 1;
    }
    else
    {
      m_bytesPerVoxel = 4;
    }

    // calc length of on data trace in bytes
    m_traceLen = 240 + m_numSamples * m_bytesPerVoxel; 
    if(m_traceLen <= 240) 
    {
      Logger::Log("Invalid trace length", m_traceLen);
      fclose(m_inFile); m_inFile = 0; 
      return false;
    }

    // calc total number of traces
    m_numTraces = (m_fileSize - 3600) / (m_traceLen);
    
    // get first trace header
    fseek(m_inFile, 3600, SEEK_SET);
    fread(m_trcHdr, 1, 240, m_inFile);
    
    // calculate number of traces per slice based on
    // original field record number (trcHdr[9-12])
    int segNum = i4(m_trcHdr, 9);
    int tracesPerSlice = 0;
    for(int i = 0; i < m_numTraces; i++)
    {
      // get ith trace header
      fseek(m_inFile, 3600 + (m_traceLen * i), SEEK_SET);
      fread(m_trcHdr, 1, 240, m_inFile);

      // compare segNum and field record number of current trace
      if(i4(m_trcHdr, 9) != segNum)
      {
        tracesPerSlice = i;
        break;
      }
    }

    // calculate size of one slice in bytes
    m_sliceSize = tracesPerSlice * (240 + m_numSamples * m_bytesPerVoxel);

    // get number of slices based on filesize and slicesize
    m_numSlices = static_cast<int>((m_fileSize - 3600) / m_sliceSize);
    
    // read first data trace
    ReadTrace(1);

    // inline and offline offset
    m_inlineOffset = i4(m_inptrc, 9);
    m_crosslineOffset = i4(m_inptrc, 21);

    // done
    FE();
    return true;
  }
  else
  {
    Logger::Log("cannot open file", filename);
    FE();
    return false;
  }
}
//============================================================================
bool SegyManager::Close()
{
  if(m_inFile) 
  {
    fclose(m_inFile);
    m_inFile = 0;
  }

  return true;
}
//============================================================================
osg::Image* SegyManager::GetImage()
{
  int xs = GetNumTraces() / GetNumSlices();
  int ys = GetNumSlices();
  int zs = GetSamplesPerTrace();

  // build result volume
  osg::ref_ptr<osg::Image> resImg = new osg::Image;

  switch (GetBytesPerVoxel())
  {
  case 1:
    resImg->allocateImage(xs, ys, zs, GL_LUMINANCE, GL_UNSIGNED_BYTE);
    break;
  case 2:
    resImg->allocateImage(xs, ys, zs, GL_LUMINANCE, GL_UNSIGNED_SHORT);
    break;
  default:
    Logger::Log("Unsupported voxel size", (int)GetBytesPerVoxel());
    break;
  }

  int numTraces = GetNumTraces();

  // fill res image
  for (int x = 0; x < xs; x++)
  {
    for (int y = 0; y < ys; y++)
    {
      int idx = x + (y * xs);
      if(idx % (numTraces / 10)  == 0) 
      {
        Logger::Log("Reading trace", idx);
      }

      ReadTrace(idx);
      WriteTraceToImage(resImg, x, y);
    }
  }
  
  return resImg.release();
}
//============================================================================
void SegyManager::WriteTraceToImage(osg::Image* resImg, int x, int y)
{
  if(m_inFile == 0)
  {
    return;
  }

  if(m_bytesPerVoxel == 2)
  {
    for(int z = 0; z < m_numSamples; z++)
    {
      unsigned short* data = (unsigned short*)resImg->data(x, y, z);
      float val = m_data[m_numSamples - z - 1];
      data[0] = val;
    }
  }
  else if(m_bytesPerVoxel == 1)
  {
    for(int z = 0; z < m_numSamples; z++)
    {
      unsigned char* data = (unsigned char*)resImg->data(x, y, z);
      float val = m_data[m_numSamples - z - 1];
      data[0] = val;
    }
  }
}
//============================================================================
float SegyManager::GetSample(int idx)
{
  float smp;
  float* dat = (float*)(m_inptrc+240);
  short* int2ptr = (short*) dat;
  if(m_format == 3)
  {
    smp = swapi2(int2ptr[idx]);
  }
  else
  {
    smp = 0;
  }
  return smp;
}
//============================================================================
void SegyManager::ReadTrace(int n)
{
  int  l;

  if(m_inFile == NULL) 
  {
    return;
  }

  fseek(m_inFile, 3600 + (n - 1) * m_traceLen, SEEK_SET);
  l = fread(m_inptrc, 1, m_traceLen, m_inFile );

  m_ctr = n;

  for(n=0; n < m_numSamples; n++) 
  {
    m_data[n] =  GetSample(n) + 32768;
  }
}
//============================================================================
void SegyManager::TrcHeadShow()
{}
//============================================================================
void SegyManager::BinHeadShow()
{}
//============================================================================
void SegyManager::TxtHeadShow()
{}
//============================================================================
int SegyManager::GetTracesPerSlice()
{
  return m_numTraces / m_numSlices; 
}
//============================================================================
int SegyManager::GetSamplesPerTrace()
{
  return m_numSamples;
}
//============================================================================
int SegyManager::GetNumSlices()
{
  return m_numSlices;
}
//============================================================================
int SegyManager::Save(osg::Image* resImg, const char* path, osg::ref_ptr<VolumeInfo> volInfo)
{
  FS();

  int xs, ys, zs;
  xs = resImg->s();
  ys = resImg->t();
  zs = resImg->r();

  m_crosslineOffset = volInfo->crosslineOffset;
  m_inlineOffset = volInfo->inlineOffset;

  char   txtHdr[SIZE_TXT_HDR];
  char   binHdr[SIZE_BIN_HDR];
  char   trcHdr[SIZE_TRC_HDR];
  char   trcBuf[SIZE_TRC_BUFFER];

  short* trcDat = (short*)(trcBuf + SIZE_TRC_HDR);
  static char Seg_Y_Default_Header[SIZE_TXT_HDR + 1] = "";

  // -------------------
  // saving
  short  numSamples, sampleInt;
  FILE* outfile;
  
  numSamples = zs;
  sampleInt = 4000;

  outfile = fopen(path, "wb");
  if(outfile == 0)
  {
    Logger::Log("Cannot open output file");
    return 0;
  }

  memset(txtHdr, 0, SIZE_TXT_HDR);

  // write textual header
  fwrite(txtHdr, 1, SIZE_TXT_HDR, outfile);

  // clear bin header
  memset(binHdr, 0, SIZE_BIN_HDR);

  // set bin header
  si4(binHdr,  5, 1);               // line number
  si4(binHdr,  9, 1);               // reel number
  si2(binHdr, 13, zs);              // data traces per ensemble
  si2(binHdr, 15, 0);               // auxiliary traces per ensemble
  si2(binHdr, 17, sampleInt);       // sample interval in microseconds
  si2(binHdr, 21, numSamples);      // samples per data trace
  si2(binHdr, 25, 3);               // data format
  si2(binHdr, 27, 0);               // ensemble fold
  si2(binHdr, 29, 4);               // trace sorting

  // write bin header
  fwrite(binHdr, 1, SIZE_BIN_HDR, outfile);

  // write data traces
  for(int y = 0; y < ys; y++)
  {
    for(int x = 0; x < xs; x++)
    {
      // clear trace header
      memset(trcHdr, 0, SIZE_TRC_HDR);

      // fill trace header
      si4(trcHdr,   1,          x+1);
      si4(trcHdr,   5,            x);
      si4(trcHdr,   9,            y + m_inlineOffset);
      si4(trcHdr,  13,          x+1);
      si4(trcHdr,  21,            x + m_crosslineOffset);
      si2(trcHdr,  29,            1);
      si2(trcHdr,  35,            1);
      si4(trcHdr,  37,            1);
      si2(trcHdr,  71,            1);
      si4(trcHdr,  73,            x);
      si4(trcHdr,  77,            y);
      si2(trcHdr, 115,   numSamples);
      si2(trcHdr, 117,    sampleInt);

      // append trace header
      memcpy(trcBuf, trcHdr, SIZE_TRC_HDR);

      for(int z = 0; z < numSamples; z++)
      {
        unsigned short* data = (unsigned short*)resImg->data(x, y, z);
        trcDat[numSamples - z - 1] = swapi2((short)data[1] - 32768);
      }
      fwrite(trcBuf, 1, numSamples * sizeof(short) + SIZE_TRC_HDR, outfile);
    }
  }

  fclose(outfile);

  Logger::Log("Done");
  FE();
  return 1;
}
//============================================================================
void SegyManager::TextHeaderToEBCDIC( char* buf )
{
  int n;

  for(n = 0; n < SIZE_TXT_HDR; n++)
  {
    buf[n] = asebc(buf[n]);
  }
}
