#ifndef SegyLoader_h__
#define SegyLoader_h__

#include <stdio.h>
#include <string.h>

#include "SegyConstants.h"
#include "VolumeInfo.h"

namespace osg
{
	template <typename T> class ref_ptr; 
  class Image;
}

class SegyManager
{
public:
  SegyManager();
  ~SegyManager();

  bool Open(const char*);
  bool Close();
  int Save(osg::Image* resImg, const char* path, osg::ref_ptr<VolumeInfo> volInfo);

  osg::Image* GetImage();
  void WriteTraceToImage(osg::Image* resImg, int x, int z);

  void TrcHeadShow();
  void BinHeadShow();
  void TxtHeadShow();
  void ReadTrace(int n);
  void TextHeaderToEBCDIC(char* buf);

  float GetSample(int idx);
  int GetTracesPerSlice();
  int GetSamplesPerTrace();
  int GetNumSlices();

  inline int GetSampleInterval() const { return m_sampleInterval; }
  inline int GetBytesPerVoxel() const { return m_bytesPerVoxel; }
  inline int GetFormat() const { return m_format; }
  inline int GetTraceLength() const { return m_traceLen; }
  inline int GetFileSize() const { return m_fileSize; }
  inline int GetSliceSize() const { return m_sliceSize; }
  inline int GetNumTraces() const { return m_numTraces; }
  inline int GetInlineOffset() const { return m_inlineOffset; }
  inline int GetCrosslineOffset() const { return m_crosslineOffset; }
  inline int GetTimeOffset() const { return m_timeOffset; }

protected:

private:

  FILE* m_inFile;
  char  m_txtHdr [SIZE_TXT_HDR];
  char  m_binHdr [SIZE_BIN_HDR];
  char  m_trcHdr [SIZE_TRC_HDR];
  char  m_inptrc [SIZE_TRC_BUFFER];
  char  m_trcBuff[SIZE_TRC_BUFFER];
  float m_data [SIZE_TRC_BUFFER];

  int m_sampleInterval;

  // volume dimensions
  int m_numSamples;
  int m_numSlices;
  int m_numTraces;

  int m_inlineOffset;
  int m_crosslineOffset;
  int m_timeOffset;

  int m_format;
  int m_bytesPerVoxel;
  int m_traceLen;
  int m_ctr;

  int m_fileSize;
  int m_sliceSize;
  float m_min;
};

#endif // SegyLoader_h__