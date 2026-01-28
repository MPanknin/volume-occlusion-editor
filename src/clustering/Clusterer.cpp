#include "Clusterer.h"

#include <list>
#include <limits>
#include <iostream>

Point2D::Point2D(int _x, int _y) : x(_x), y(_y) {
}


Point2D::Point2D(const Point2D &cpy){
	x = cpy.x;
	y = cpy.y;
}

unsigned int Point2D::getSquaredDist(const Point2D &to) const{
	return (x - to.x) * (x - to.x) + (y - to.y) * (y - to.y);
}

unsigned int Point2D::getDist(const Point2D &to) const{
	return sqrt(static_cast<float>(getSquaredDist(to)));
}


Point2D Point2D::operator+(const Point2D& rhs){
	return Point2D(x + rhs.x, y + rhs.y);
}


Point2D& Point2D::operator+=(const Point2D& rhs){
	x += rhs.x;
	y += rhs.y;

	return *this;
}


Point2D Point2D::operator-(const Point2D& rhs){
	return Point2D(x - rhs.x, y - rhs.y);
}


Point2D Point2D::operator/(int rhs){
	return Point2D(x / rhs, y / rhs);
}


Point2D& Point2D::operator/=(int rhs){
	x /= rhs;
	y /= rhs;

	return *this;
}


Point2D& Point2D::operator=(const Point2D& rhs){
	x = rhs.x;
	y = rhs.y;

	return *this;
}


//------------------------------------------------------------------------------------------------------------


BoundingBox::BoundingBox(const Point2D &min, const Point2D &max) : mMin(min), mMax(max)
{

}


BoundingBox::~BoundingBox(void){
}


bool BoundingBox::isOverlapping(const BoundingBox &other){	
	/*return ((mMax.x > other.mMin.x && mMin.x < other.mMin.x) || (mMin.x < other.mMax.x && mMax.x > other.mMax.x)) &&
		   ((mMax.y > other.mMin.y && mMin.y < other.mMin.y) || (mMin.y < other.mMax.y && mMax.y > other.mMax.y));*/

	/*return 
	((mMin.x < other.mMin.x && mMax.x > other.mMin.x) || 
	 (mMin.x > other.mMin.x && mMax.x < other.mMax.x) ||
	 (mMin.x < other.mMax.x && mMax.x > other.mMax.x)) &&

	((mMin.y < other.mMin.y && mMax.y > other.mMin.y) || 
	 (mMin.y > other.mMin.y && mMax.y < other.mMax.y) ||
	 (mMin.y < other.mMax.y && mMax.y > other.mMax.y));*/

	return 
	((mMin.x <= other.mMin.x && mMax.x >= other.mMin.x) || 
	 (mMin.x >= other.mMin.x && mMax.x <= other.mMax.x) ||
	 (mMin.x <= other.mMax.x && mMax.x >= other.mMax.x)) &&

	((mMin.y <= other.mMin.y && mMax.y >= other.mMin.y) || 
	 (mMin.y >= other.mMin.y && mMax.y <= other.mMax.y) ||
	 (mMin.y <= other.mMax.y && mMax.y >= other.mMax.y));


}


BoundingBox BoundingBox::operator+(const BoundingBox &rhs){
	Point2D newMin;
	Point2D newMax;

	if(mMin.x <= rhs.mMin.x){
		newMin.x = mMin.x;
		if(mMin.y <= rhs.mMin.y){
			newMin.y = mMin.y;
		}
		else{
			newMin.y = rhs.mMin.y;
		}
	}
	else{
		newMin.x = rhs.mMin.x;
		if(mMin.y <= rhs.mMin.y){
			newMin.y = mMin.y;
		}
		else{
			newMin.y = rhs.mMin.y;
		}
	}



	if(mMax.x <= rhs.mMax.x){
		newMax.x = rhs.mMax.x;
		if(mMax.y <= rhs.mMax.y){
			newMax.y = rhs.mMax.y;
		}
		else{
			newMax.y = mMax.y;
		}
	}
	else{
		newMax.x = mMax.x;
		if(mMax.y <= rhs.mMax.y){
			newMax.y = rhs.mMax.y;
		}
		else{
			newMax.y = mMax.y;
		}
	}

	return BoundingBox(newMin, newMax);


}

BoundingBox& BoundingBox::operator=(const BoundingBox &rhs){
	mMin = rhs.mMin;
	mMax = rhs.mMax;

	return *this;
}


//------------------------------------------------------------------------------------------------------------



Clusterer::Clusterer(const std::vector<Point2D> * const data) : mData(data)
{
	//mClusterInfo.reserve(mData->size()); 
	mClusterInfo = std::vector<int>(mData->size(), -1);
}


Clusterer::~Clusterer(void)
{
}


void Clusterer::mergeClusters(void){
	std::list<BoundingBox> bBoxes;
	int xMin, yMin, xMax, yMax;

	unsigned int numClusters = mClusterPoints.size();
	std::list<int> bBoxClusterRel; //stores which bounding box contains which cluster
	std::vector<int> replacedClusters;
	replacedClusters.reserve(numClusters);
	
	for(int i=0; i<numClusters; i++){
		xMin = yMin = INT_MAX;
		xMax = yMax = INT_MIN;

		int cInfS = mClusterInfo.size();
		for(int j=0; j<cInfS; j++){
			
			if(i == mClusterInfo[j]){
				Point2D p = mData->data()[j];
				if(xMin > p.x){
					xMin = p.x;
				}
				if(yMin > p.y){
					yMin = p.y;
				}

				if(xMax < p.x){
					xMax = p.x;
				}
				if(yMax < p.y){
					yMax = p.y;
				}

			}
		}


		bBoxes.push_back(BoundingBox(Point2D(xMin, yMin), Point2D(xMax, yMax)));
		bBoxClusterRel.push_back(i);
		replacedClusters.push_back(i);
	}

	/*std::list<BoundingBox>::iterator bbIt0 = bBoxes.begin();
	std::list<BoundingBox>::iterator bbIt1 = bbIt0;
	bbIt1++;
	std::list<BoundingBox>::iterator bbEnd = bBoxes.end();
	
	std::list<int>::iterator bClRelIt0 = bBoxClusterRel.begin();
	std::list<int>::iterator bClRelIt1 = bClRelIt0;
	bClRelIt1++;*/

	std::list<BoundingBox>::iterator bbIt0;
	std::list<BoundingBox>::iterator bbIt1;
	std::list<BoundingBox>::iterator bbEnd;
	
	std::list<int>::iterator bClRelIt0;
	std::list<int>::iterator bClRelIt1;
	

	bool converged = false;

	while(!converged){

		bbIt0 = bBoxes.begin();
		bbIt1 = bbIt0;
		bbIt1++;
		bbEnd = bBoxes.end();

		
		bClRelIt0 = bBoxClusterRel.begin();
		bClRelIt1 = bClRelIt0;
		bClRelIt1++;

		converged = true;

		while(bbIt0 != bbEnd){
			while(bbIt1 != bbEnd){
				if((*bbIt0).isOverlapping(*bbIt1)){
					converged = false;

					*bbIt0 = *bbIt0 + *bbIt1;
					bBoxes.erase(bbIt1);

					bbIt1 = bbIt0;
					//bbIt1++;

					replacedClusters[*bClRelIt1] = *bClRelIt0;
					bBoxClusterRel.erase(bClRelIt1);
					bClRelIt1 = bClRelIt0;
					//bClRelIt1++;

				}

				bbIt1++;
				bClRelIt1++;
			}

			bbIt0++;
			if(bbIt0 == bbEnd){
				break;
			}
			bbIt1 = bbIt0;
			bbIt1++;

			bClRelIt0++;
			bClRelIt1 = bClRelIt0;
			bClRelIt1++;
		}
	}

	//DEBUG
	//std::cout<<"Anzahl der Boxen: "<<bBoxes.size()<<std::endl;
	


	mClusterPoints.clear();
	bbIt0 = bBoxes.begin();
	bbEnd = bBoxes.end();
	while(bbIt0 != bbEnd){
		mClusterPoints.push_back((*bbIt0).mMin + (((*bbIt0).mMax - (*bbIt0).mMin) / 2));

		bbIt0++;
	}


	int cInfS = mClusterInfo.size();
	for(int i=0; i<cInfS; i++){
		mClusterInfo[i] = replacedClusters[mClusterInfo[i]];
	}

}

