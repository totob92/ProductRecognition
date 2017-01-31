#include "opencv2/opencv.hpp"

class KeyPoint_Center{

public:
	KeyPoint_Center(cv::KeyPoint keyPointScene, cv::KeyPoint KeyPointModel, cv::Point center);

	cv::KeyPoint keyPointScene;
	cv::KeyPoint KeyPointModel;
	cv::Point center;
};