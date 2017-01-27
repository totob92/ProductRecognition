#include "Keypoint_Detection.h"

void Keypoint_Detection(cv::Mat image, cv::Ptr<cv::Feature2D> detector, std::vector<cv::KeyPoint> &keypoints_image){
	bool visualize_everything = true;
	detector->detect(image, keypoints_image);
	std::cout << keypoints_image.size() << " Keypoints found on model" << std::endl;

	//DA TOGLIERE
	if (visualize_everything){
		//show detected keypoints
		cv::Mat target_copy, scene_copy;
		cv::drawKeypoints(image, keypoints_image, target_copy, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Model", target_copy);

		std::cout << "Keypoint detected" << std::endl;
		cv::waitKey();
		cv::destroyAllWindows();
	}
	
}

std::vector<std::vector<cv::KeyPoint>> DBSCAN_keypoints(cv::Mat image,std::vector<cv::KeyPoint> *keypoints, float eps, int minPts)
{
	std::vector<std::vector<cv::KeyPoint>> clusters;
	std::vector<bool> clustered;
	std::vector<int> noise;
	std::vector<bool> visited;
	std::vector<int> neighborPts;
	std::vector<int> neighborPts_;
	int c;

	int noKeys = keypoints->size();

	//init clustered and visited
	for (int k = 0; k < noKeys; k++)
	{
		clustered.push_back(false);
		visited.push_back(false);
	}

	//C =0;
	c = 0;
	clusters.push_back(std::vector<cv::KeyPoint>()); //will stay empty?

	//for each unvisted point P in dataset keypoints
	for (int i = 0; i < noKeys; i++)
	{
		if (!visited[i])
		{
			//Mark P as visited
			visited[i] = true;
			neighborPts = regionQuery(keypoints, &keypoints->at(i), eps);
			if (neighborPts.size() < minPts)
				//Mark P as Noise
				noise.push_back(i);
			else
			{
				
				clusters.push_back(std::vector<cv::KeyPoint>());
				//expand cluster
				// add P to cluster c
				clustered[i] = true;
				clusters[c].push_back(keypoints->at(i));
				//for each point P' in neighborPts
				for (int j = 0; j < neighborPts.size(); j++)
				{
					//if P' is not visited
					if (!visited[neighborPts[j]])
					{
						//Mark P' as visited
						neighborPts_ = regionQuery(keypoints, &keypoints->at(neighborPts[j]), eps);
						visited[neighborPts[j]] = true;

						if (neighborPts_.size() >= minPts)
						{
							neighborPts.insert(neighborPts.end(), neighborPts_.begin(), neighborPts_.end());
						}
					}
					// if P' is not yet a member of any cluster
					// add P' to cluster c
					if (!clustered[neighborPts[j]])
						clusters[c].push_back(keypoints->at(neighborPts[j]));
						clustered[neighborPts[j]] = true;
				}
			}
			c++;
		}
	}
	
	cv::Mat target_copy;
	printf("%d", clusters.size());
	if (clusters.size()-1 > 1){
		cv::drawKeypoints(image, clusters[0], target_copy, cv::Scalar(0, 255, 0), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Cluster", target_copy);
		cv::imwrite("cluster0.png", target_copy);
		cvWaitKey();
		cv::drawKeypoints(image, clusters[1], target_copy, cv::Scalar(255, 0, 0), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Cluster", target_copy);
		cv::imwrite("cluster1.png", target_copy);
		cvWaitKey();
		cv::drawKeypoints(image, clusters[2], target_copy, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Cluster", target_copy);
		cv::imwrite("cluster2.png", target_copy);
		cvWaitKey();
		cv::drawKeypoints(image, clusters[3], target_copy, cv::Scalar(120, 120, 120), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Cluster", target_copy);
		cv::imwrite("cluster3.png", target_copy);
		cvWaitKey();
	}
	else{
		cv::drawKeypoints(image, clusters[0], target_copy, cv::Scalar(0, 255, 0), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Cluster", target_copy);
		cv::imwrite("cluster0.png", target_copy);
		cvWaitKey();
	}
	
	return clusters;
}

std::vector<int> regionQuery(std::vector<cv::KeyPoint> *keypoints, cv::KeyPoint *keypoint, float eps)
{
	float dist;
	std::vector<int> retKeys;
	for (int i = 0; i< keypoints->size(); i++)
	{
		dist = sqrt(pow((keypoint->pt.x - keypoints->at(i).pt.x), 2) + pow((keypoint->pt.y - keypoints->at(i).pt.y), 2));
		if (dist <= eps && dist != 0.0f)
		{
			retKeys.push_back(i);
		}
	}
	return retKeys;
}