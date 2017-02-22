#include "opencv2/opencv.hpp"
#include "Centers_From_KeyPoints.h"
#define PI 3.14159265

extern bool VISUALIZE_EVERYTHING;

cv::Point get_Center_Of_Image(cv::Mat image);

cv::Point get_Center_From_Formula(cv::KeyPoint keypoint_i, cv::KeyPoint keypoint_j, cv::Point center);

Centers_From_KeyPoints get_Centers(cv::Mat model_1, std::vector<cv::KeyPoint> keypoints_match,
	std::vector<cv::DMatch> filtered_match_1, std::vector<cv::KeyPoint> keypoints_model_1, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene);

std::vector<Centers_From_KeyPoints> get_Centers_Multiple(std::vector<cv::Mat> models,
	std::vector<std::vector<cv::DMatch>> filtered_matches, std::vector<std::vector<cv::KeyPoint>> keypoints_models, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene);

std::vector<Centers_From_KeyPoints> DBSCAN_Centers(cv::Mat image, Centers_From_KeyPoints points, float eps, int minPts);

std::vector<std::vector<Centers_From_KeyPoints>> DBSCAN_Centers_Multiple(cv::Mat image, std::vector<Centers_From_KeyPoints> points, float eps, int minPts);

std::vector<int> region_Query(Centers_From_KeyPoints points, Center_From_KeyPoint point, float eps);