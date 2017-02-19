#include "Utils.h"

cv::Point getCenterOfImage(cv::Mat image){

	cv::Point result = cvPoint(0, 0);
	result.x = image.cols / 2;
	result.y = image.rows / 2;

	return result;

}

cv::Point get_Center_From_Formula(cv::KeyPoint keypoint_model, cv::KeyPoint keypoint_scene, cv::Point center){

	float teta_model = keypoint_model.angle;
	float teta_scene = keypoint_scene.angle;
	float teta = teta_model - teta_scene;

	float scale_model = keypoint_model.size;
	float scale_scene = keypoint_scene.size;

	cv::Point center_relative_model = cv::Point(0, 0);
	center_relative_model.x = center.x - keypoint_model.pt.x;
	center_relative_model.y = center.y - keypoint_model.pt.y;

	float temp_0 = center_relative_model.x*cos(teta*PI / 180) - center_relative_model.y*sin(teta*PI / 180);
	float temp_1 = center_relative_model.y*cos(teta*PI / 180) + center_relative_model.x*sin(teta*PI / 180);
	
	temp_0 = temp_0 * (scale_scene / scale_model);
	temp_1 = temp_1 * (scale_scene / scale_model);

	temp_0 = temp_0 + keypoint_scene.pt.x;
	temp_1 = temp_1 + keypoint_scene.pt.y;

	cv::Point result = cv::Point(temp_0, temp_1);

	return result;
}

std::vector<cv::Point> get_Centroid(std::vector<std::vector<cv::Point>> clusters, cv::Mat image){
	
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
	return result;
}

Centers_From_KeyPoints get_Centers(cv::Mat model, std::vector<cv::KeyPoint> keypoints_match,
	std::vector<cv::DMatch> filtered_match, std::vector<cv::KeyPoint> keypoints_model, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene){

	cv::Mat temp_image;
	scene.copyTo(temp_image);
	cv::Point centerofimage = getCenterOfImage(model);
	Centers_From_KeyPoints corrispondenze;

	for (int i = 0; i < keypoints_match.size(); i++){

		int pos_keypoint_model = filtered_match.at(i).trainIdx;
		int pos_keypoint_scene = filtered_match.at(i).queryIdx;

		cv::Point centro = get_Center_From_Formula(keypoints_model.at(pos_keypoint_model),keypoints_scene.at(pos_keypoint_scene), centerofimage);

		Center_From_KeyPoint corr = Center_From_KeyPoint(keypoints_model.at(pos_keypoint_model),keypoints_scene.at(pos_keypoint_scene), centro);

		corrispondenze.centers_from_keypoints.push_back(corr);

		cv::Scalar color = cv::Scalar(0, 0, 255);
		cv::circle(temp_image, centro, 2, color, -1);
	}

	if (VISUALIZE_EVERYTHING == true){
		cv::namedWindow("Centri non Clusterizzati", cv::WINDOW_NORMAL);
		cv::imshow("Centri non Clusterizzati", temp_image);
		cv::waitKey();
		cv::destroyAllWindows();
	}

	return corrispondenze;
}

std::vector<Centers_From_KeyPoints> get_Centers_Multiple(std::vector<cv::Mat> models,
	std::vector<std::vector<cv::DMatch>> filtered_matches, std::vector<std::vector<cv::KeyPoint>> keypoints_models, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene){

	std::vector<Centers_From_KeyPoints> result;
	cv::Mat temp_image;
	
	for (int j = 0; j < models.size(); j++){
		scene.copyTo(temp_image);
		cv::Mat model = models.at(j);
		std::vector<cv::DMatch> filtered_match = filtered_matches.at(j);
		std::vector<cv::KeyPoint> keypoints_model = keypoints_models.at(j);
		cv::Point centerofimage = getCenterOfImage(model);
		Centers_From_KeyPoints temp = Centers_From_KeyPoints();

		for (int i = 0; i < filtered_match.size(); i++){

			int pos_keypoint_model = filtered_match.at(i).trainIdx;
			int pos_keypoint_scene = filtered_match.at(i).queryIdx;

			cv::Point centro = get_Center_From_Formula(keypoints_model.at(pos_keypoint_model), keypoints_scene.at(pos_keypoint_scene), centerofimage);

			Center_From_KeyPoint corr = Center_From_KeyPoint(keypoints_model.at(pos_keypoint_model), keypoints_scene.at(pos_keypoint_scene), centro);

			temp.centers_from_keypoints.push_back(corr);

			cv::Scalar color = cv::Scalar(0, 0, 255);
			cv::circle(temp_image, centro, 2, color, -1);
		}

		result.push_back(temp);
		if (VISUALIZE_EVERYTHING == true){
			cv::namedWindow("Centri non Clusterizzati", cv::WINDOW_NORMAL);
			cv::imshow("Centri non Clusterizzati", temp_image);
			cv::waitKey();
			cv::destroyAllWindows();
		}
	}

	return result;
}

std::vector<Centers_From_KeyPoints> DBSCAN_Centers(cv::Mat image, Centers_From_KeyPoints points, float eps, int minPts)
{
	std::vector<Centers_From_KeyPoints> clusters;
	std::vector<bool> clustered;
	std::vector<int> noise;
	std::vector<bool> visited;
	std::vector<int> neighborPts;
	std::vector<int> neighborPts_;
	int c;

	int noKeys = points.centers_from_keypoints.size();

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
			neighborPts = region_Query(points, points.atPosition(i), eps);
			if (neighborPts.size() < minPts)
				//Mark P as Noise
				noise.push_back(i);
			else
			{

				clusters.push_back(Centers_From_KeyPoints());
				//expand cluster
				// add P to cluster c
				clustered[i] = true;
				clusters[c].insertIn(points.atPosition(i));
				//for each point P' in neighborPts
				for (int j = 0; j < neighborPts.size(); j++)
				{
					//if P' is not visited
					if (!visited[neighborPts[j]])
					{
						//Mark P' as visited
						neighborPts_ = region_Query(points, points.atPosition(neighborPts[j]), eps);
						visited[neighborPts[j]] = true;

						if (neighborPts_.size() >= minPts)
						{
							neighborPts.insert(neighborPts.end(), neighborPts_.begin(), neighborPts_.end());
						}
					}
					// if P' is not yet a member of any cluster
					// add P' to cluster c
					if (!clustered[neighborPts[j]])
						clusters[c].insertIn(points.atPosition(neighborPts[j]));
					clustered[neighborPts[j]] = true;
				}
				c++;
			}
		}
	}
	
	if (VISUALIZE_EVERYTHING == true){
		for (int i = 0; i < clusters.size(); i++){
			Centers_From_KeyPoints cluster = clusters.at(i);
			cv::Scalar color = cv::Scalar(100 * i, 255 / (i + 1), 255 - (i * 50));
			for (int j = 0; j < cluster.centers_from_keypoints.size(); j++){
				cv::circle(image, cluster.atPosition(j).center, 2, color, -1);
			}
			cv::namedWindow("Cluster", cv::WINDOW_NORMAL);
			cv::imshow("Cluster", image);
			cvWaitKey();
			cvDestroyAllWindows();
		}
	}

	return clusters;
}

std::vector<int> region_Query(Centers_From_KeyPoints points, Center_From_KeyPoint point, float eps)
{
	float dist;
	std::vector<int> retKeys;
	for (int i = 0; i< points.centers_from_keypoints.size(); i++)
	{
		dist = sqrt(pow((point.center.x - points.atPosition(i).center.x), 2) + pow((point.center.y - points.atPosition(i).center.y), 2));
		if (dist <= eps && dist != 0.0f)
		{
			retKeys.push_back(i);
		}
	}
	return retKeys;
}