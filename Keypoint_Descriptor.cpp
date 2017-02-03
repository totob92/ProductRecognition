#include "Keypoint_Descriptor.h"

void Keypoint_Descriptor(cv::Mat image, std::vector<cv::KeyPoint> keypoints_image, cv::Ptr<cv::Feature2D> descriptor, cv::Mat &descriptor_image){

	descriptor->compute(image, keypoints_image, descriptor_image);
	std::cout << "Descriptor computed on scene" << std::endl;

}

void Keypoint_Descriptor_Multiple(std::vector<cv::Mat> models, std::vector<std::vector<cv::KeyPoint>> keypoints_image, cv::Ptr<cv::Feature2D> descriptor, std::vector<cv::Mat> &descriptor_image){

	for (int i = 0; i < models.size(); i++){
		descriptor->compute(models.at(i), keypoints_image.at(i), descriptor_image.at(i));
		std::cout << "Descriptor computed on image " << i+1<< std::endl;
	}

}