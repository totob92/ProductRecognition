#include "opencv2/opencv.hpp"




void Descriptor_Matching(cv::Mat model, cv::Mat scene, cv::Mat descriptor_model, cv::Mat descriptor_scene, std::vector<cv::KeyPoint> keypoints_model,
	std::vector<cv::KeyPoint> keypoints_scene, cv::Ptr<cv::DescriptorMatcher> &matcher, std::vector<cv::DMatch> &filtered_match, std::vector<cv::DMatch> &all_match);

void Keypoints_From_Filtered_Matches(std::vector<cv::DMatch> filtered_matches, std::vector<cv::KeyPoint> keypoints_image, cv::Mat image, std::vector<cv::KeyPoint> &keypoints_match);