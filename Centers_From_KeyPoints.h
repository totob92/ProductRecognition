#include "opencv2/opencv.hpp"
#include "Center_From_KeyPoint.h"

class Centers_From_KeyPoints{

public:
	Centers_From_KeyPoints(std::vector<Center_From_KeyPoint> centers_from_kp);
	Centers_From_KeyPoints();

	std::vector<Center_From_KeyPoint> centers_from_keypoints;

};