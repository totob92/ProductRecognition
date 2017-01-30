#include "opencv2/opencv.hpp"
#include "../KeyPoint_Center.h"

cv::Point getCenterOfImage(cv::Mat image);

cv::Point getCenterKeypoints(cv::KeyPoint keypoint_i, cv::KeyPoint keypoint_j, cv::Point center);

std::vector<cv::Point> trovaBaricentri(std::vector<std::vector<cv::Point>> clusters, cv::Mat image);

std::vector<KeyPoint_Center> trovaCentri(cv::Mat model_1, std::vector<cv::KeyPoint> keypoints_match,
	std::vector<cv::DMatch> filtered_match_1, std::vector<cv::KeyPoint> keypoints_model_1, std::vector<cv::KeyPoint> keypoints_scene, cv::Mat scene, std::vector<cv::Point> *centri);


std::vector<std::vector<KeyPoint_Center>> DBSCAN_centers_plus(cv::Mat image, std::vector<KeyPoint_Center> points, float eps, int minPts);

std::vector<int> regionQueryCenter_Plus(std::vector<KeyPoint_Center> points, KeyPoint_Center point, float eps);










int contaOccorenze(cv::Point p, std::vector<cv::Point> points);