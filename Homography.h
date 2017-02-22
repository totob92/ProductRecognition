#include "opencv2/opencv.hpp"
#include "Utils.h"
#include "MyColors.h"


void Multi_Homography(cv::Mat scene, std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::Mat> models, std::vector<std::vector<cv::DMatch>> filtered_matches, 
	std::vector<std::vector<cv::KeyPoint>> keypoints_models);

void MyHomography(cv::Mat model, cv::Mat scene, std::vector<cv::KeyPoint> keypoints_model, std::vector<cv::KeyPoint> keypoints_scene, cv::Scalar boxColor);

void Multi_MyHomography(std::vector<cv::Mat> models, cv::Mat scene, std::vector<std::vector<Centers_From_KeyPoints>> corrispondenze_plus);


