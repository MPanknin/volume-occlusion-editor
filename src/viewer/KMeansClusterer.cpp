#include "KMeansClusterer.h"

#include <iostream>


KMeansClusterer::KMeansClusterer(const std::vector<Point2D> * const data, unsigned int numClusters, unsigned int reclusteringThresh) 
	: Clusterer(data), mNumClusters(numClusters), mReclusteringThresh(reclusteringThresh)
{
	mMinXVal = INT_MAX;
	mMaxXVal = INT_MIN;
	mMinYVal = INT_MAX;
	mMaxYVal = INT_MIN;

	std::vector<Point2D>::const_iterator datIt = mData->begin();
	std::vector<Point2D>::const_iterator datEnd = mData->end();
	while(datIt != datEnd){

		if((*datIt).x < mMinXVal){
			mMinXVal = (*datIt).x;
		}

		if((*datIt).x > mMaxXVal){
			mMaxXVal = (*datIt).x;
		}

		if((*datIt).y < mMinYVal){
			mMinYVal = (*datIt).y;
		}

		if((*datIt).y > mMaxYVal){
			mMaxYVal = (*datIt).y;
		}
		
		datIt++;
	}
}


KMeansClusterer::~KMeansClusterer(void)
{
}


Point2D KMeansClusterer::calculateClusterCenter(void){
	return Point2D(mMinXVal + (static_cast<float>(rand()) / RAND_MAX) * (mMaxXVal - mMinXVal), 
				   mMinYVal + (static_cast<float>(rand()) / RAND_MAX) * (mMaxYVal - mMinYVal));
}


void KMeansClusterer::clusterData(void){
	//std::cout<<"equal goes it loose "<<mData->size()<<std::endl;
	mClusterPoints.clear();
	Point2D *tmpClusters = new Point2D[mNumClusters];
	unsigned int *numPointsInCluster = new unsigned int[mNumClusters];
	bool *clusterConverged = new bool[mNumClusters];

	//initialize cluster points
	for(int i=0; i<mNumClusters; i++){
		
		/*mClusterPoints.push_back(Point2D(mMinXVal + (static_cast<float>(rand()) / RAND_MAX) * (mMaxXVal - mMinXVal), 
										 mMinYVal + (static_cast<float>(rand()) / RAND_MAX) * (mMaxYVal - mMinYVal)));*/

		mClusterPoints.push_back(calculateClusterCenter());
		mLastClusterPoints.push_back(mClusterPoints.back());
		clusterConverged[i] = false;

	}

	////DEBUG
	//for(int i=0; i<mNumClusters; i++){
	//	std::cout<<"Cluster "<<i<<" ("<<mClusterPoints.data()[i].x<<", "<<mClusterPoints.data()[i].y<<", "<<")   "<<numPointsInCluster[i]<<std::endl;
	//}


	bool isConverged = false;

	//DEBUG
	int cnt = 0;

	while(!isConverged)
  {

		//assign points to cluster
		for(int i=0; i<mNumClusters; i++){
			numPointsInCluster[i] = 0;
			tmpClusters[i] = Point2D();
		}

		int s = mData->size();
		for(int i=0; i<s; i++)
    {
			unsigned int minDist = UINT_MAX;
			int cluster;

			for(int j=0; j<mNumClusters; j++)
      {
#if _MSC_VER > 1600
				unsigned int dist = mData->data()[i].getSquaredDist(mClusterPoints.data()[j]);
#else
        unsigned int dist = mData->at(i).getSquaredDist(mClusterPoints[j]);
#endif
				if(dist < minDist)
        {
					minDist = dist;
					cluster = j;
				}
			}	

			mClusterInfo[i] = cluster;
			numPointsInCluster[cluster]++;
		}

		////DEBUG
		//std::cout<<std::endl;
		//for(int i=0; i<mNumClusters; i++){
		//	std::cout<<"Cluster "<<i<<" ("<<mClusterPoints.data()[i].x<<", "<<mClusterPoints.data()[i].y<<", "<<")   "<<numPointsInCluster[i]<<std::endl;
		//}

		//rebuild cluster
		for(int i=0; i<s; i++)
    {
#if _MSC_VER > 1600
			tmpClusters[mClusterInfo[i]] += mData->data()[i];
		}
	
		for(int i=0; i<mNumClusters; i++)
    {
			if(numPointsInCluster[i] == 0)
      {
				mClusterPoints.data()[i] = calculateClusterCenter();
			}
			else
      {
				mClusterPoints.data()[i] =  tmpClusters[i] / numPointsInCluster[i];
			}
#else
      tmpClusters[mClusterInfo[i]] += mData->at(i);
    }

    for(int i=0; i<mNumClusters; i++)
    {
      if(numPointsInCluster[i] == 0)
      {
        mClusterPoints[i] = calculateClusterCenter();
      }
      else
      {
        mClusterPoints[i] =  tmpClusters[i] / numPointsInCluster[i];
      }
#endif
		}


		////DEBUG
		//std::cout<<std::endl;
		//for(int i=0; i<mNumClusters; i++){
		//	std::cout<<"Cluster "<<i<<" ("<<mClusterPoints.data()[i].x<<", "<<mClusterPoints.data()[i].y<<", "<<")   "<<numPointsInCluster[i]<<std::endl;
		//}


		isConverged = true;
		for(int i=0; i<mNumClusters; i++)
    {
			//if(!clusterConverged[i])
      //{
				////DEBUG
				//int dist = mClusterPoints.data()[i].getDist(mLastClusterPoints.data()[i]);
				//std::cout<<"dist: "<<dist<<" ";

				//if(dist <= mReclusteringThresh){
				//	clusterConverged[i] = true;
				//}

				if(mClusterPoints.at(i).getDist(mLastClusterPoints.at(i)) <= mReclusteringThresh && numPointsInCluster[i] > 0)
        {
					clusterConverged[i] = true;
				}
        else{
          clusterConverged[i] = false;
        }

			//}

			mLastClusterPoints.at(i) = mClusterPoints.at(i);
			isConverged &= clusterConverged[i];

		}
	}

	

	////DEBUG
	////std::cout<<numPointsInCluster[0]<<" "<<numPointsInCluster[1]<<" "<<numPointsInCluster[2]<<std::endl;
	//std::cout<<std::endl;
	//std::cout<<std::endl;
	//std::cout<<std::endl;
	//for(int i=0; i<mNumClusters; i++){
	//	std::cout<<"Cluster "<<i<<" ("<<mClusterPoints.at(i).x<<", "<<mClusterPoints.at(i).y<<", "<<")   "<<numPointsInCluster[i]<<std::endl;
	//}


	/*for(int i=0; i<mClusterInfo.size(); i++){
		
		std::cout<<mClusterInfo[i]<<" ";
	}
	std::cout<<std::endl;*/



	delete [] tmpClusters;
	delete [] numPointsInCluster;
	delete [] clusterConverged;
	
}


