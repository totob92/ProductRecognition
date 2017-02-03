#include "opencv2/opencv.hpp"
#include "Centers_From_KeyPoints.h"
#define PI 3.14159265

cv::Point getCenterOfImage(cv::Mat image);

cv::Point getCenterKeypoints(cv::KeyPoint keypoint_i, cv::KeyPoint keypoint_j, cv::Point center);

std::vector<cv::Point> trovaBaricentri(std::vector<std::vector<cv::Point>> clusters, cv::Mat image);

Centers_From_KeyPoints trovaCentri(cv::Mat model_1, std::vector<cv::KeyPoint> keypoints_match,
	std::vector<cv::DMatch> filtered_match_1, std::vector<cv::KeyPoint> keypoints_model_1, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene);


std::vector<std::vector<Center_From_KeyPoint>> DBSCAN_centers_plus(cv::Mat image, std::vector<Center_From_KeyPoint> points, float eps, int minPts);

std::vector<int> regionQueryCenter_Plus(std::vector<Center_From_KeyPoint> points, Center_From_KeyPoint point, float eps);










int contaOccorenze(cv::Point p, std::vector<cv::Point> points);