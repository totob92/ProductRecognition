#include "Box.h"


Box::Box() { point0 = cv::Point(0, 0); point1 = cv::Point(0, 0); point2 = cv::Point(0, 0); point3 = cv::Point(0, 0); }

Box::Box(cv::Point2f p0, cv::Point2f p1, cv::Point2f p2, cv::Point2f p3){
	point0 = p0;
	point1 = p1;
	point2 = p2;
	point3 = p3;
}

std::vector<cv::Point2f> Box::toVector(){
	
	std::vector<cv::Point2f> result;
	result.push_back(point0);
	result.push_back(point1);
	result.push_back(point2);
	result.push_back(point3);

	return result;
}

void Box::drawYourself(cv::Mat image, cv::Scalar color, int dim_line ){

	cv::line(image, point0, point1, color, dim_line);
	cv::line(image, point1, point2, color, dim_line);
	cv::line(image, point2, point3, color, dim_line);
	cv::line(image, point3, point0, color, dim_line);

}