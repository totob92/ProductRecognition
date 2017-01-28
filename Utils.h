#include "opencv2/opencv.hpp"

cv::Point getCenterOfImage(cv::Mat image);

cv::Point getCenterKeypoints(cv::KeyPoint keypoint_i, cv::KeyPoint keypoint_j, cv::Point center);