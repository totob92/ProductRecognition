#include "Keypoint_Descriptor.h"

void Keypoint_Descriptor(cv::Mat image, std::vector<cv::KeyPoint> keypoints_image, cv::Ptr<cv::Feature2D> descriptor, cv::Mat &descriptor_image){

descriptor->compute(image, keypoints_image, descriptor_image);
std::cout << "Descriptor computed" << std::endl;

}