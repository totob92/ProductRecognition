#include "Center_From_KeyPoint.h"

Center_From_KeyPoint::Center_From_KeyPoint(cv::KeyPoint keyPointM, cv::KeyPoint keyPointS, cv::Point c){
	keyPointModel = keyPointM;
	keyPointScene = keyPointS;
	center = c;
}
