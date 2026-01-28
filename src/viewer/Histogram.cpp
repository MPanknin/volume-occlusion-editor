#include "Histogram.h"
#include "Logger.h"

// ====================================================
Histogram::Histogram( int numBins ) 
  : m_numBins(numBins), m_normData(0)
{
  m_normData = new unsigned char[m_numBins];

  for(int i = 0; i < m_numBins; i++)
  {
    m_binBuffer.push_back(0);
    m_normData[i] = 0;
  }

  m_meta = new HistogramMeta;
  m_meta->posX = 0;
  m_meta->posY = 0;
  m_meta->posZ = 0;
  m_meta->intensity = 0;
}

// ====================================================
Histogram::~Histogram(void)
{
  m_binBuffer.clear();
  if(m_normData) 
  {
    delete[] m_normData;
    m_normData = 0;
  }
  if(m_meta)
  {
    delete m_meta;
    m_meta = 0;
  }
}

// ====================================================
void Histogram::DeleteBinBuffer()
{
  m_binBuffer.clear();
}

// ====================================================
void Histogram::AddValue( BinType value )
{
  int binSize = 256 / m_numBins;

  for(int i = 0; i < m_numBins; i++)
  {
    if(value >= i * binSize && value < (i + 1) * binSize)
    {
      //Logger::Log("value and target bin: ", (int)value, i * binSize, i * binSize + (binSize - 1));
      m_binBuffer[i]++;
    }
  }
}

// ====================================================
void Histogram::Normalize()
{
  if(m_normData == 0) return;

  // build histogram 
  // min / max from bins
  float maxVal = INT_MIN;
  float minVal = INT_MAX;

  for(int i = 0; i < m_numBins; i++)
  {
    float val = m_binBuffer[i];
    maxVal = val > maxVal ? val: maxVal;
    minVal = val < minVal ? val: minVal;
  }

  //Logger::Log("bins min max", minVal, maxVal);

  // normalize
  for(int i = 0; i < m_numBins; i++)
  {
    m_binBuffer[i] -= minVal;
    m_binBuffer[i] *= ((float) 255 / maxVal);

    // set normalized value into norm data
    // simple truncation to unsigned char problematic?
    m_normData[i] = m_binBuffer[i];
  }
}

// ====================================================
void Histogram::SetOrigin( int x, int y, int z )
{
  m_meta->posX = x;
  m_meta->posY = y;
  m_meta->posZ = z;
}
// ====================================================
void Histogram::SetIntensity( unsigned char intensity )
{
  m_meta->intensity = intensity;
}
// ====================================================
void Histogram::SetBinValue( int binNum, int value )
{
  m_normData[binNum] = value;
}

// ====================================================
// ====================================================
// ====================================================
// ====================================================
// ====================================================