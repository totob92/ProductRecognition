#include "MyColors.h"

MyColors::MyColors() {
	colors.push_back(cv::Scalar(255, 0, 0));
	colors.push_back(cv::Scalar(0, 255, 0));
	colors.push_back(cv::Scalar(0, 0, 255));
	colors.push_back(cv::Scalar(255, 255, 0));
	colors.push_back(cv::Scalar(255, 0, 255));
	colors.push_back(cv::Scalar(0, 255, 255));
}