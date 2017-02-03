#include "Centers_From_KeyPoints.h"

Centers_From_KeyPoints::Centers_From_KeyPoints(std::vector<Center_From_KeyPoint> centers_from_kp){
	centers_from_keypoints = centers_from_kp;
}

Centers_From_KeyPoints::Centers_From_KeyPoints(){
	centers_from_keypoints = std::vector<Center_From_KeyPoint>();
}