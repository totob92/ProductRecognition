#include "opencv2/opencv.hpp"
#include "Center_From_KeyPoint.h"

class Centers_From_KeyPoints{

public:
	Centers_From_KeyPoints(std::vector<Center_From_KeyPoint> centers_from_kp);
	Centers_From_KeyPoints();
	Center_From_KeyPoint atPosition(int i);
	void insertIn(Center_From_KeyPoint ckp);
	std::vector<cv::KeyPoint> get_Vector_Key_Point_Model();
	std::vector<cv::KeyPoint> get_Vector_Key_Point_Scene();
	std::vector<cv::Point> get_Vector_Center();


	std::vector<Center_From_KeyPoint> centers_from_keypoints;
};