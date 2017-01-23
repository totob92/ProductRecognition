#include "opencv2/opencv.hpp"

void Homography(cv::Mat model, cv::Mat scene, std::vector<cv::KeyPoint> keypoints_model, std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::DMatch> filtered_match);

void Multi_Homography(cv::Mat scene, std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::Mat> models, std::vector<std::vector<cv::DMatch>> filtered_matches, 
	std::vector<std::vector<cv::KeyPoint>> keypoints_models);
