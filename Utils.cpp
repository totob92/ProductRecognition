#include "Utils.h"

cv::Point getCenterOfImage(cv::Mat image){

	cv::Point result = cvPoint(0, 0);
	result.x = image.rows / 2;
	result.y = image.cols / 2;

	return result;

}

cv::Point getCenterKeypoints(cv::KeyPoint keypoint_i, cv::KeyPoint keypoint_j, cv::Point center){

	float teta_i = keypoint_i.angle;
	float teta_j = keypoint_j.angle;
	float teta = teta_i - teta_j;

	float scale_i = keypoint_i.size;
	float scale_j = keypoint_j.size;

	cv::Point j_primo = cv::Point(0, 0);
	j_primo.x = center.x - keypoint_j.pt.x;
	j_primo.y = center.y - keypoint_j.pt.y;

	float temp_0 = j_primo.x*cos(teta) - j_primo.y*sin(teta);
	float temp_1 = j_primo.y*cos(teta) + j_primo.x*sin(teta);
	
	temp_0 = temp_0 * (scale_i / scale_j);
	temp_1 = temp_1 * (scale_i / scale_j);

	temp_0 = temp_0 + keypoint_i.pt.x;
	temp_1 = temp_1 + keypoint_i.pt.y;

	cv::Point result = cv::Point(abs(temp_0), abs(temp_1));

	return result;
}
