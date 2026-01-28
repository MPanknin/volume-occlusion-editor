#ifndef Histogram_h__
#define Histogram_h__

#include <vector>

typedef unsigned char BinType;

struct HistogramMeta
{
  int posX;
  int posY;
  int posZ;

  BinType intensity;
};

struct Centroid
{
  int value;
  BinType intensity;
};

class Histogram
{
public:
  Histogram(int numBins);
  virtual ~Histogram(void);

  const unsigned char* GetNormData() const { return m_normData; }
  int GetNumBins() const {return m_numBins;}
  
  void Normalize();
  void DeleteBinBuffer();

  void AddValue(BinType value);
  void SetBinValue(int binNum, int value);

  const HistogramMeta* GetMeta() const { return m_meta; }
  void SetOrigin(int x, int y, int z);
  void SetIntensity(unsigned char intensity);


protected:
  unsigned char* m_normData;
  std::vector<float> m_binBuffer;
  int m_numBins;

  HistogramMeta* m_meta;
};

#endif // Histogram_h__
