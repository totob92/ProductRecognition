#include "Centers_From_KeyPoints.h"

Centers_From_KeyPoints::Centers_From_KeyPoints(std::vector<Center_From_KeyPoint> centers_from_kp){
	centers_from_keypoints = centers_from_kp;
}

Centers_From_KeyPoints::Centers_From_KeyPoints(){
	centers_from_keypoints = std::vector<Center_From_KeyPoint>();
}

Center_From_KeyPoint Centers_From_KeyPoints::atPosition(int i){
	return centers_from_keypoints.at(i);
}

void Centers_From_KeyPoints::insertIn(Center_From_KeyPoint ckp){
	centers_from_keypoints.push_back(ckp);
}

std::vector<cv::KeyPoint> Centers_From_KeyPoints::get_Vector_Key_Point_Model(){

	std::vector<cv::KeyPoint> result;
	for (int i = 0; i < centers_from_keypoints.size(); i++){
		result.push_back(centers_from_keypoints.at(i).keyPointModel);
	}
	return result;

}
std::vector<cv::KeyPoint> Centers_From_KeyPoints::get_Vector_Key_Point_Scene(){

	std::vector<cv::KeyPoint> result;
	for (int i = 0; i < centers_from_keypoints.size(); i++){
		result.push_back(centers_from_keypoints.at(i).keyPointScene);
	}
	return result;

}
std::vector<cv::Point> Centers_From_KeyPoints::get_Vector_Center(){

	std::vector<cv::Point> result;
	for (int i = 0; i < centers_from_keypoints.size(); i++){
		result.push_back(centers_from_keypoints.at(i).center);
	}
	return result;

}