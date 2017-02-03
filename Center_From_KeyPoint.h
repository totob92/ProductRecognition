#include "opencv2/opencv.hpp"

class Center_From_KeyPoint{

public:
	Center_From_KeyPoint(cv::KeyPoint KeyPointModel, cv::KeyPoint keyPointScene, cv::Point center);

	cv::KeyPoint keyPointScene;
	cv::KeyPoint keyPointModel;
	cv::Point center;
};
