#include <string>

#include "VolumeInfo.h"
#include "ConfigFile.h"
#include "Logger.h"
#include "ApplicationPaths.h"

// ====================================================
VolumeInfo::VolumeInfo()
{
  file = "";
  numBytes = 1;
  dimX = dimY = dimZ = 0;
  distX = distY = distZ = 1;
  inlineOffset = crosslineOffset = 0;
}
// ====================================================
VolumeInfo::~VolumeInfo()
{
}
// ====================================================
void VolumeInfo::Open(const char* path)
{
  FS();

  ConfigFile config(path);

  file = config.read<std::string>("file");
  numBytes = config.read<int>("numBytes");

  dimX = config.read<int>("dimX");
  dimY = config.read<int>("dimY");
  dimZ = config.read<int>("dimZ");

  distX = config.read<float>("distX");
  distY = config.read<float>("distY");
  distZ = config.read<float>("distZ");

  inlineOffset = config.read<int>("inOff");
  crosslineOffset = config.read<int>("crossOff");
  timeOffset = config.read<int>("timeOff");

  sampleInterval = config.read<int>("sampleInterval");

  FE();
}
// ====================================================
void VolumeInfo::Save(const char* path)
{
  FS();

  ConfigFile config(path);

  config.add<string>("file", VOL_IMAGE);
  config.add<int>("numBytes", numBytes);

  config.add<int>("dimX", dimX);
  config.add<int>("dimY", dimY);
  config.add<int>("dimZ", dimZ);

  config.add<float>("distX", distX);
  config.add<float>("distY", distY);
  config.add<float>("distZ", distZ);

  config.add<int>("inOff", inlineOffset);
  config.add<int>("crossOff", crosslineOffset);
  config.add<int>("timeOff", timeOffset);

  config.add<int>("sampleInterval", sampleInterval);

  std::ofstream outfile;
  outfile.open(path);
  outfile << config;
  outfile.close();

  FE();
}
// ====================================================
void VolumeInfo::Print()
{
  FS();

  Logger::Log("File", file.c_str());
  Logger::Log("Num bytes", numBytes);
  Logger::Log("Dimensions",  dimX, dimY, dimZ);
  Logger::Log("Slice distances",  distX, distY, distZ);
  Logger::Log("Initial offsets", inlineOffset, crosslineOffset, timeOffset);
  Logger::Log("Sample interval", sampleInterval);

  FE();
}

// ====================================================
// ====================================================
// ====================================================
// ====================================================