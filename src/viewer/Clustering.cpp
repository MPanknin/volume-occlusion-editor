//
//#ifdef WIN32
//	#include <windows.h>
//#endif
//
//#include <iostream>
//
//#include "IL/il.h"
//#include "IL/ilu.h"
//
//
//#include <vector>
//
//#include "KMeansClusterer.h"
//
//
//static const float PI = 3.14159265;
//
//
//
//void writeImgData(ILubyte *imgData, int x, int y, int imgW, ILubyte r, ILubyte g, ILubyte b){
//	ILubyte *p = imgData + (y * imgW * 3 + x * 3);
//
//	*p       = r;
//	*(p + 1) = g;
//	*(p + 2) = b;
//
//}
//
//int main(int argc, char* argv[])
//{
//	std::cout<<"Clustering Test"<<std::endl;
//
//
//	//- - - read data from image - - -
//	ilInit();
//
//	ILuint img;
//	ilGenImages(1, &img);
//

//	ilBindImage(img);
//
//	if(!ilLoadImage("test5.png")){
//	
//		ILenum err = ilGetError();
//
//		std::cout<<"ERROR opening file "<<err<<std::endl;		
//	}
//	 
//	ILuint imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
//	ILuint imgHeight = ilGetInteger(IL_IMAGE_HEIGHT); 
//
//	//DEBUG
//	std::cout<<"Image: "<<imgWidth<<" "<<imgHeight<<std::endl;
//
//	ILubyte *imgData = ilGetData();
//
//	std::vector<Point2D> gDataPoints;
//
//	for(int y=0; y<imgHeight; y++){
//		for(int x=0; x<imgWidth; x++){
//			if(*imgData != 0 && *(imgData + 1) != 0 && *(imgData + 2) != 0){ //everything which is not black matters
//				Point2D p;
//				p.x = x;
//				p.y = y;
//				gDataPoints.push_back(p);	
//			}
//
//			imgData += 3;
//		}
//	}
//
//	std::cout<<"number of points: "<<gDataPoints.size()<<std::endl;
//
//	
//	//- - - k-means clustering - - - 
//	unsigned int initialNumClusters = 20;
//
//	KMeansClusterer gClusterer(&gDataPoints);
//	gClusterer.setNumClusters(initialNumClusters);
//
//	int tStart = GetTickCount();
//
//	gClusterer.clusterData();
//	gClusterer.mergeClusters();
//
//	int tStop = GetTickCount();
//	
//	std::cout<<"time: "<<tStop - tStart<<" ms"<<std::endl;
//
//	//- - - write result data to file - - -
//	std::vector<ILubyte> r;
//	std::vector<ILubyte> g;
//	std::vector<ILubyte> b;
//
//	float colStep = PI / (initialNumClusters - 1);
//
//	for(int i=0; i<initialNumClusters; i++){
//		r.push_back(255 * (0.5f * (sin(i * colStep + 0.78f)) + 1.0f));
//		g.push_back(255 * (0.5f * (cos(i * colStep + PI)) + 1.0f));
//		b.push_back(255 * (1.0f / PI * (i * colStep)));
//	}
//
//	imgData = ilGetData();
//
//	for(int i=0; i<gDataPoints.size(); i++){
//		writeImgData(imgData, gDataPoints.data()[i].x, gDataPoints.data()[i].y, imgWidth, r[gClusterer.getClusterInfo()[i]], 
//																						  g[gClusterer.getClusterInfo()[i]], 
//																						  b[gClusterer.getClusterInfo()[i]]);
//	}
//
//	int numClusterPoints = gClusterer.getClusterPoints().size();
//	
//	std::cout<<"number of clusters: "<<numClusterPoints<<std::endl;
//
//	for(int i=0; i<numClusterPoints; i++){
//		Point2D cp = gClusterer.getClusterPoints().data()[i];
//
//		int ext = 5;
//
//		for(int y=-ext; y<=ext; y++){
//			int yImg = cp.y + y;
//			if(yImg >= 0 && yImg < imgHeight){
//				writeImgData(imgData, cp.x, yImg, imgWidth, 255, 255, 255);
//			}
//		}
//
//		for(int x=-ext; x<=ext; x++){
//			int xImg = cp.x + x;
//			if(xImg >= 0 && xImg < imgWidth){
//				writeImgData(imgData, cp.x + x, cp.y, imgWidth, 255, 255, 255);
//			}
//		}
//		
//	}
//	
//	ilEnable(IL_FILE_OVERWRITE);
//	ilSaveImage("out.png");
//	
//
//
//	Point2D mean;
//	
//	
//	for(int i=0; i<numClusterPoints; i++){
//		mean += gClusterer.getClusterPoints().data()[i];
//	}
//	mean /= numClusterPoints;
//
//	float variance = 0.0f;
//	for(int i=0; i<numClusterPoints; i++){
//		variance += gClusterer.getClusterPoints().data()[i].getSquaredDist(mean);
//	}
//
//	variance /= numClusterPoints;
//
//
//	std::cout<<"mean: ("<<mean.x<<", "<<mean.y<<")"<<std::endl;
//	std::cout<<"variance: "<<variance<<std::endl;
//
//
//
//	return 0;
//}
//
