#include <assert.h>

#include <osg\Image>

#include "SegyLoader.h"
#include "Logger.h"
#include "Util.h"

//============================================================================
SegyLoader::SegyLoader()
{
  m_inFile = 0;
  m_min = 0;
}
//============================================================================
SegyLoader::~SegyLoader()
{
}
//============================================================================
bool SegyLoader::Open(const char* filename)
{
  FS();
  if(m_inFile) 
  {
    fclose(m_inFile);
  }

  m_inFile = fopen(filename, "rb");

  if(m_inFile)
  {
    
    fseek(m_inFile, 0, SEEK_END);
    m_fileSize = ftell(m_inFile);

    fseek(m_inFile, 0, SEEK_SET);

    fread(m_txtHdr, 1, 3200, m_inFile);
    fread(m_binHdr, 1, 400, m_inFile);

    m_sampleInterval   = i2(m_binHdr, 17) / 1000000.;
    m_numSamples = i2(m_binHdr, 21);
    m_format = i2(m_binHdr, 25);

    if(m_sampleInterval <= 0) 
      goto ERR;
    if(m_numSamples <= 0)
      goto ERR;
    if(m_format < 1 || m_format > 8)  
      goto ERR;

    if (m_format == 3) 
      m_bytesPerVoxel = 2;
    else if(m_format == 8) 
      m_bytesPerVoxel = 1;
    else
      m_bytesPerVoxel = 4;

    m_traceLen = 240 + m_numSamples * m_bytesPerVoxel; 
    
    if(m_traceLen <= 240) 
      goto ERR;

    m_numTraces = (m_fileSize - 3600) / (m_traceLen);

    fseek(m_inFile, 3600, SEEK_SET);
    fread(m_trcHdr, 1, 240, m_inFile);
    
    // calculate number of traces per slice based on
    // original field record number (trcHdr[9-12])
    int segNum = i4(m_trcHdr, 9);
    int tracesPerSlice = 0;
    for(int i = 0; i < m_numTraces; i++)
    {
      fseek(m_inFile, 3600 + (m_traceLen * i), SEEK_SET);
      fread(m_trcHdr, 1, 240, m_inFile);

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

    ReadTrace(1);

    return true;
ERR:
    Logger::Log("Bad format!");
    fclose(m_inFile); 
    m_inFile = NULL; 

    FE();
    return false;
  }
  else
  {
    Logger::Log("Can't open file", filename);

    FE();
    return false;
  }
}
//============================================================================
bool SegyLoader::Close()
{
  if(m_inFile) 
  {
    fclose(m_inFile);
  }

  return true;
}
//============================================================================
void SegyLoader::TrcDataShow(osg::Image* resImg, int x, int y)
{
  if(m_inFile == 0)
  {
    return;
  }

  // get min value
  for(int i = 0; i < m_numSamples; i++)
  {
    m_min = m_min < m_data[i] ? m_min : m_data[i];
  }
  if(m_bytesPerVoxel == 2)
  {
    for(int z = 0; z < m_numSamples; z++)
    {
      unsigned short* data = (unsigned short*)resImg->data(x, y, z);
      float val = m_data[z] - m_min;
      data[0] = val;
    }
  }
  else if(m_bytesPerVoxel == 1)
  {
    for(int z = 0; z < m_numSamples; z++)
    {
      unsigned char* data = (unsigned char*)resImg->data(x, y, z);
      float val = m_data[z] - m_min;
      data[0] = val;
    }
  }
}
//============================================================================
void SegyLoader::TrcHeadShow()
{}
//============================================================================
void SegyLoader::BinHeadShow()
{}
//============================================================================
void SegyLoader::TxtHeadShow()
{}
//============================================================================
float SegyLoader::GetSample(int idx)
{
  float   smp;
  int*    xmp = (int*)&smp;
  float*  dat = (float*)(m_inptrc+240);

  short*         int2ptr = (short*)       dat;
  int*           int4ptr = (int*)         dat;
  signed char*   int1ptr = (signed char*) dat;

  if(m_format==1)
  {
    smp =  dat[idx];
    ibm2ieee(&smp,1);
  }
  else if(m_format==2)
  {
    smp = swapi4(int4ptr[idx]);
  }
  else if(m_format==3)
  {
    smp = swapi2(int2ptr[idx]);
  }
  else if(m_format==4)
  {
    smp = dat[idx];
  }
  else if(m_format==5)
  {
    *xmp = swapi4(int4ptr[idx]);
  }
  else if(m_format==6)
  {
    smp = int1ptr[idx];
  }
  else if(m_format==8)
  {
    smp = int1ptr[idx];
  }
  else
    smp = 0;

  return smp;
}
//============================================================================
void SegyLoader::ReadTrace(int n)
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
    m_data[n] =  GetSample(n);
  }
}
//============================================================================
int SegyLoader::GetTracesPerSlice()
{
  return m_numTraces / m_numSlices; 
}
//============================================================================
int SegyLoader::GetSamplesPerTrace()
{
  return m_numSamples;
}
//============================================================================
int SegyLoader::GetNumSlices()
{
  return m_numSlices;
}
//============================================================================
int SegyLoader::Save(osg::Image* resImg, const char* path)
{
  FS();

  int xs, ys, zs;
  xs = resImg->s();
  ys = resImg->t();
  zs = resImg->r();

  Logger::Log("Dimensions", xs, ys, zs);

  char   txtHdr[TXT_HDR];
  char   binHdr[BIN_HDR];
  char   trcHdr[TRC_HDR];
  char   trcBuf[BUFF_SIZE];

  short* trcDat = (short*)(trcBuf + TRC_HDR);
  static char Seg_Y_Default_Header[TXT_HDR + 1] = "";

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

  // write textual header
  fwrite(txtHdr, 1, TXT_HDR, outfile);

  // clear bin header
  memset(binHdr, 0, BIN_HDR);

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
  fwrite(binHdr, 1, BIN_HDR, outfile);

  // write data traces
  for(int y = 0; y < ys; y++) // 100
  {
    for(int x = 0; x < xs; x++) // 50
    {
      // clear trace header
      memset(trcHdr, 0, TRC_HDR);

      // fill trace header
      si4(trcHdr,   1,          x+1);
      si4(trcHdr,   9,            y);
      si4(trcHdr,  13,          x+1);
      si4(trcHdr,  21,            x);
      si2(trcHdr, 115,   numSamples);
      si2(trcHdr, 117,    sampleInt);

      // append trace header
      memcpy(trcBuf, trcHdr, TRC_HDR);

      for(int z = 0; z < numSamples; z++)
      {
        unsigned short* data = (unsigned short*)resImg->data(x, y, z);
        trcDat[z] = swapi2(data[1]);
      }
      fwrite(trcBuf, 1, numSamples * sizeof(short) + TRC_HDR, outfile);

      //Logger::Log("x: y:", x, y);
    }
  }

  fclose(outfile);

  FE();
  return 1;
}
//============================================================================
void SegyLoader::TextHeaderToEBCDIC( char* buf )
{
  int n;

  for(n = 0; n < TXT_HDR; n++)
  {
    buf[n] = asebc(buf[n]);
  }
}
