#ifndef K_MEANS_CLUSTERER_H
#define K_MEANS_CLUSTERER_H

#include "Clusterer.h"
class KMeansClusterer : public Clusterer
{
	//----------CONSTRUCTORS UND DESTURCTOR------------
	public:
		KMeansClusterer(const std::vector<Point2D> * const data, unsigned int numClusters = 3, unsigned int reclusteringThresh = 3);
		virtual ~KMeansClusterer(void);

	//----------MEMBER VARIABLES-----------------------
	private:
		unsigned int mNumClusters;
		
		std::vector<Point2D> mLastClusterPoints;

		unsigned int mReclusteringThresh; ///threshold value in pixels to finish clustering algorithm

		int mMinXVal;
		int mMaxXVal;
		int mMinYVal;
		int mMaxYVal;

		

	//----------MEMBER FUNCTIONS-----------------------
	private:
		Point2D calculateClusterCenter(void);

	public:
		void setNumClusters(unsigned int nc){mNumClusters = nc;}
		void clusterData(void);
    void setReclusteringThresh(unsigned int t){mReclusteringThresh = t;}
		

		
};
#endif
