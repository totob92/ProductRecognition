#include "Utils.h"

cv::Point getCenterOfImage(cv::Mat image){

	cv::Point result = cvPoint(0, 0);
	result.x = image.rows / 2;
	result.y = image.cols / 2;

	return result;

}