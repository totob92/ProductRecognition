#include "opencv2/opencv.hpp"

class Box{
	public:
		Box();
		Box(cv::Point2f point0, cv::Point2f point1, cv::Point2f point2, cv::Point2f point3);
		std::vector<cv::Point2f> toVector();
		void drawYourself(cv::Mat image, cv::Scalar color, int dim_line);
	
		cv::Point2f point0;
		cv::Point2f point1;
		cv::Point2f point2;
		cv::Point2f point3;
};