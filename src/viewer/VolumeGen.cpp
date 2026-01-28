//#include "VolumeManager.h"
//#include "osg/Vec3f"
//#include "osgDB/WriteFile"
//
//using namespace osg;
//int main()
//{
//  VolumeManager::i()->createEmpty(256, 256, 256);
//  VolumeManager::i()->fillSphere(Vec3f(128, 128, 128), 40, 200);
//  VolumeManager::i()->fillSphere(Vec3f(200, 128, 128), 20, 50);
//  //VolumeManager::i()->fillSphere(Vec3f(120, 128, 128), 20, 120);
//
//  //VolumeManager::i()->fillSphere(Vec3f(80, 128, 240), 20, 100);
//  //VolumeManager::i()->fillSphere(Vec3f(100, 128, 240), 20, 110);
//  //VolumeManager::i()->fillSphere(Vec3f(120, 128, 240), 20, 120);
//
//
//  Image* img = VolumeManager::i()->getVolume();
//  osgDB::writeImageFile(*img, "temp/sphere.dds");
//
//  return 0;
//};