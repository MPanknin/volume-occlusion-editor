#ifndef CLUSTERER_H
#define CLUSTERER_H

#include <vector>

class Point2D{
	//----------CONSTRUCTORS UND DESTURCTOR------------
	public:
		Point2D(int _x=0, int _y=0);
		Point2D(const Point2D &cpy);
		~Point2D(void){}

	//----------MEMBER VARIABLES-----------------------
	public:	
		int x;
		int y;

	//----------MEMBER FUNCTIONS-----------------------
	public:
		unsigned int getSquaredDist(const Point2D &to) const;
		unsigned int getDist(const Point2D &to) const;

		Point2D  operator+(const Point2D& rhs);
		Point2D& operator+=(const Point2D& rhs);
		Point2D  operator-(const Point2D& rhs);

		Point2D& operator=(const Point2D& rhs);

		Point2D  operator/(int rhs);
		Point2D&  operator/=(int rhs);

};


/**
Axis aligned bounding box
*/
class BoundingBox{
	//----------CONSTRUCTORS UND DESTURCTOR------------
	public:
		BoundingBox(const Point2D &min, const Point2D &max);
		~BoundingBox(void);

	//----------MEMBER VARIABLES-----------------------
	public:	
		Point2D mMin;
		Point2D mMax;

	//----------MEMBER FUNCTIONS-----------------------
	public:
		bool isOverlapping(const BoundingBox &other); 
		BoundingBox operator+(const BoundingBox &rhs);
		BoundingBox& operator=(const BoundingBox &rhs);

};

class Clusterer
{
	//----------CONSTRUCTORS UND DESTURCTOR------------
	public:
		Clusterer(const std::vector<Point2D> * const data);
		virtual ~Clusterer(void);

	//----------MEMBER VARIABLES-----------------------
	protected:
		const std::vector<Point2D> * const mData; ///stores subsequent x,y values of points to cluster
		std::vector<int> mClusterInfo; ///stores the cluster for each point
		std::vector<Point2D> mClusterPoints;

	//----------MEMBER FUNCTIONS-----------------------
	public:
		const std::vector<int>& getClusterInfo(void){return mClusterInfo;}

		virtual void clusterData(void) = 0;
		void mergeClusters(void);

		const std::vector<Point2D>& getClusterPoints(void) const {return mClusterPoints;}
	
};

#endif

