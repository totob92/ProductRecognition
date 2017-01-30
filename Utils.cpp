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

int contaOccorenze(cv::Point p, std::vector<cv::Point> points){

	int result = 0;
	for (int i = 0; i < points.size(); i++){
		if (p.x == points.at(i).x && p.y == points.at(i).y){
			result++;
		}
	}
	return result;

}


