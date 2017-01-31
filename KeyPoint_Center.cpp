#include "KeyPoint_Center.h"

KeyPoint_Center::KeyPoint_Center(cv::KeyPoint keyPointM, cv::KeyPoint keyPointS, cv::Point c){
	KeyPointModel = keyPointM;
	keyPointScene = keyPointS;
	center = c;
}
