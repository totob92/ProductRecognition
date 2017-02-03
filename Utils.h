#include "opencv2/opencv.hpp"
#include "Centers_From_KeyPoints.h"
#define PI 3.14159265

extern bool VISUALIZE_EVERYTHING;

cv::Point getCenterOfImage(cv::Mat image);

cv::Point get_Center_From_Formula(cv::KeyPoint keypoint_i, cv::KeyPoint keypoint_j, cv::Point center);

std::vector<cv::Point> get_Centroid(std::vector<std::vector<cv::Point>> clusters, cv::Mat image);

Centers_From_KeyPoints get_Centers(cv::Mat model_1, std::vector<cv::KeyPoint> keypoints_match,
	std::vector<cv::DMatch> filtered_match_1, std::vector<cv::KeyPoint> keypoints_model_1, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene);


std::vector<Centers_From_KeyPoints> DBSCAN_Centers(cv::Mat image, Centers_From_KeyPoints points, float eps, int minPts);

std::vector<int> region_Query(Centers_From_KeyPoints points, Center_From_KeyPoint point, float eps);










int contaOccorenze(cv::Point p, std::vector<cv::Point> points);