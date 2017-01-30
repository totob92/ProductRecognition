#include "Utils.h"

cv::Point getCenterOfImage(cv::Mat image){

	cv::Point result = cvPoint(0, 0);
	result.x = image.cols / 2;
	result.y = image.rows / 2;

	return result;

}

cv::Point getCenterKeypoints(cv::KeyPoint keypoint_model, cv::KeyPoint keypoint_scene, cv::Point center){

	float teta_model = keypoint_model.angle;
	float teta_scene = keypoint_scene.angle;
	float teta = teta_model - teta_scene;

	float scale_model = keypoint_model.size;
	float scale_scene = keypoint_scene.size;

	cv::Point center_relative_model = cv::Point(0, 0);
	center_relative_model.x = center.x - keypoint_model.pt.x;
	center_relative_model.y = center.y - keypoint_model.pt.y;

	float temp_0 = center_relative_model.x*cos(teta) - center_relative_model.y*sin(teta);
	float temp_1 = center_relative_model.y*cos(teta) + center_relative_model.x*sin(teta);
	
	temp_0 = temp_0 * (scale_scene / scale_model);
	temp_1 = temp_1 * (scale_scene / scale_model);

	temp_0 = temp_0 + keypoint_scene.pt.x;
	temp_1 = temp_1 + keypoint_scene.pt.y;

	cv::Point result = cv::Point(temp_0, temp_1);

	return result;
}

std::vector<cv::Point> trovaBaricentri(std::vector<std::vector<cv::Point>> clusters, cv::Mat image){
	
	std::vector<cv::Point> result;

	for (int i = 0; i < clusters.size(); i++){
		std::vector<cv::Point> cluster = clusters.at(i);
		float tot_x = 0;
		float tot_y = 0;
		for (int j = 0; j < cluster.size(); j++){
			tot_x += cluster.at(j).x;
			tot_y += cluster.at(j).y;
		}
		tot_x = tot_x / cluster.size();
		tot_y = tot_y / cluster.size();
		result.push_back(cv::Point(tot_x, tot_y));
		cv::circle(image, cv::Point(tot_x, tot_y), 5, cv::Scalar(255, 0, 0), -1);

	}
	cv::namedWindow("Baricentro", cv::WINDOW_NORMAL);
	cv::imshow("Baricentro", image);
	cvWaitKey();
	return result;
}

std::vector<KeyPoint_Center> trovaCentri(cv::Mat model_1, std::vector<cv::KeyPoint> keypoints_match,
	std::vector<cv::DMatch> filtered_match_1, std::vector<cv::KeyPoint> keypoints_model_1, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene, std::vector<cv::Point> *centri){

	cv::Point centerofimage = getCenterOfImage(model_1);
	std::vector<KeyPoint_Center> corrispondenze;

	for (int i = 0; i < keypoints_match.size(); i++){

		int pos_keypoint_model = filtered_match_1.at(i).trainIdx;
		int pos_keypoint_scene = filtered_match_1.at(i).queryIdx;
		cv::Point centro = getCenterKeypoints(keypoints_model_1.at(pos_keypoint_model),
			keypoints_scene.at(pos_keypoint_scene), centerofimage);
		cv::KeyPoint temp = keypoints_scene.at(pos_keypoint_scene);
		centri->push_back(centro);

		KeyPoint_Center corr = KeyPoint_Center(keypoints_scene.at(pos_keypoint_scene),
			keypoints_model_1.at(pos_keypoint_model), centro);
		corrispondenze.push_back(corr);

		printf("Pos:[%d %d]\n", centro.x, centro.y);
		cv::Scalar color = cv::Scalar(0, 0, 255);
		cv::circle(scene, centro, 2, color, -1);
	}
	cv::namedWindow("Centri", cv::WINDOW_NORMAL);
	cv::imshow("Centri", scene);
	cv::waitKey();

	return corrispondenze;
}

std::vector<std::vector<KeyPoint_Center>> DBSCAN_centers_plus(cv::Mat image, std::vector<KeyPoint_Center> points, float eps, int minPts)
{
	std::vector<std::vector<KeyPoint_Center>> clusters;
	std::vector<bool> clustered;
	std::vector<int> noise;
	std::vector<bool> visited;
	std::vector<int> neighborPts;
	std::vector<int> neighborPts_;
	int c;

	int noKeys = points.size();

	//init clustered and visited
	for (int k = 0; k < noKeys; k++)
	{
		clustered.push_back(false);
		visited.push_back(false);
	}

	//C =0;
	c = 0;

	//for each unvisted point P in dataset keypoints
	for (int i = 0; i < noKeys; i++)
	{
		if (!visited[i])
		{
			//Mark P as visited
			visited[i] = true;
			neighborPts = regionQueryCenter_Plus(points, points.at(i), eps);
			if (neighborPts.size() < minPts)
				//Mark P as Noise
				noise.push_back(i);
			else
			{

				clusters.push_back(std::vector<KeyPoint_Center>());
				//expand cluster
				// add P to cluster c
				clustered[i] = true;
				clusters[c].push_back(points.at(i));
				//for each point P' in neighborPts
				for (int j = 0; j < neighborPts.size(); j++)
				{
					//if P' is not visited
					if (!visited[neighborPts[j]])
					{
						//Mark P' as visited
						neighborPts_ = regionQueryCenter_Plus(points, points.at(neighborPts[j]), eps);
						visited[neighborPts[j]] = true;

						if (neighborPts_.size() >= minPts)
						{
							neighborPts.insert(neighborPts.end(), neighborPts_.begin(), neighborPts_.end());
						}
					}
					// if P' is not yet a member of any cluster
					// add P' to cluster c
					if (!clustered[neighborPts[j]])
						clusters[c].push_back(points.at(neighborPts[j]));
					clustered[neighborPts[j]] = true;
				}
				c++;
			}
		}
	}

	cv::Mat target_copy = image;
	printf("%d\n", clusters.size());
	cvWaitKey();
	for (int i = 0; i<clusters.size(); i++){
		std::vector<KeyPoint_Center> cluster = clusters.at(i);
		cv::Scalar color = cv::Scalar(100 * i, 255 / (i + 1), 255 - (i * 50));
		printf("[Cluster:%d quantità:%d]\n", i, cluster.size());
		for (int j = 0; j < cluster.size(); j++){
			cv::circle(target_copy, cluster.at(j).center, 2, color, -1);
		}
		cv::namedWindow("Cluster", cv::WINDOW_NORMAL);
		cv::imshow("Cluster", target_copy);
		//cv::imwrite("cluster0.png", target_copy);
		cvWaitKey();
	}


	return clusters;
}

std::vector<int> regionQueryCenter_Plus(std::vector<KeyPoint_Center> points, KeyPoint_Center point, float eps)
{
	float dist;
	std::vector<int> retKeys;
	for (int i = 0; i< points.size(); i++)
	{
		dist = sqrt(pow((point.center.x - points.at(i).center.x), 2) + pow((point.center.y - points.at(i).center.y), 2));
		if (dist <= eps && dist != 0.0f)
		{
			retKeys.push_back(i);
		}
	}
	return retKeys;
}







//------------------------------------------inutils
int contaOccorenze(cv::Point p, std::vector<cv::Point> points){

	int result = 0;
	for (int i = 0; i < points.size(); i++){
		if (p.x == points.at(i).x && p.y == points.at(i).y){
			result++;
		}
	}
	return result;

}


