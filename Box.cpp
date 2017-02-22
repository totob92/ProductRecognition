#include "Box.h"

Box::Box() { 
	point0 = cv::Point(0, 0); point1 = cv::Point(0, 0); point2 = cv::Point(0, 0); point3 = cv::Point(0, 0); 
}

Box::Box(cv::Point2f p0, cv::Point2f p1, cv::Point2f p2, cv::Point2f p3){
	point0 = p0;
	point1 = p1;
	point2 = p2;
	point3 = p3;
}

void Box::drawYourself(cv::Mat image, cv::Scalar color, int dim_line ){

	cv::line(image, point0, point1, color, dim_line);
	cv::line(image, point1, point2, color, dim_line);
	cv::line(image, point2, point3, color, dim_line);
	cv::line(image, point3, point0, color, dim_line);

}

cv::Point2f Box::getCenter(){

	cv::Point2f result;
	result.x = ((point0.x + point1.x + point2.x + point3.x)/4);
	result.y = ((point0.y + point1.y + point2.y + point3.y)/4);
	return result;

}

float Box::getHeight(){
	return sqrt(pow(point0.x - point3.x, 2) + pow(point0.y - point3.y, 2));
}

float Box::getWidht(){
	return sqrt(pow(point0.x - point1.x, 2) + pow(point0.y - point1.y, 2));
}

void Box::printBox(){
	printf("Widht: %2.f Height: %2.f Center: x[%2.f] y[%2.f]\n", getWidht(), getHeight(), getCenter().x, getCenter().y);
}