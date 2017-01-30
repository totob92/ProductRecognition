#include "opencv2/opencv.hpp"
#include "../KeyPoint_Center.h"

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2) //opencv version 2.4.x
#include "opencv2/nonfree/nonfree.hpp"
#else  //opencv version 3.x
//to support SIFT and sURF in version 3 compile from source :(
#endif

void Keypoint_Detection(cv::Mat image, cv::Ptr<cv::Feature2D> detector, std::vector<cv::KeyPoint> &keypoints_image);

std::vector<std::vector<cv::KeyPoint>> DBSCAN_keypoints(cv::Mat image, std::vector<cv::KeyPoint> *keypoints, float eps, int minPts);

std::vector<int> regionQuery(std::vector<cv::KeyPoint> *keypoints, cv::KeyPoint *keypoint, float eps);





std::vector<std::vector<cv::Point>> DBSCAN_centers(cv::Mat image, std::vector<cv::Point> *points, float eps, int minPts);

std::vector<int> regionQueryCenter(std::vector<cv::Point> *points, cv::Point *point, float eps);

std::vector<std::vector<KeyPoint_Center>> DBSCAN_centers_plus(cv::Mat image, std::vector<KeyPoint_Center> points, float eps, int minPts);

std::vector<int> regionQueryCenter_Plus(std::vector<KeyPoint_Center> points, KeyPoint_Center point, float eps);