#include "opencv2/opencv.hpp"

extern bool VISUALIZE_EVERYTHING;

void Descriptor_Matching(cv::Mat model, cv::Mat scene, cv::Mat descriptor_model, cv::Mat descriptor_scene, std::vector<cv::KeyPoint> keypoints_model,
	std::vector<cv::KeyPoint> keypoints_scene, cv::Ptr<cv::DescriptorMatcher> &matcher, std::vector<cv::DMatch> &filtered_match, std::vector<cv::DMatch> &all_match);

void Descriptor_Matching_Multiple(std::vector<cv::Mat> models, cv::Mat scene, std::vector<cv::Mat>descriptor_models, cv::Mat descriptor_scene, std::vector<std::vector<cv::KeyPoint>> keypoints_models,
	std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::Ptr<cv::DescriptorMatcher>> &matchers, std::vector<std::vector<cv::DMatch>> &filtered_matches, std::vector<std::vector<cv::DMatch>> &all_matches);




//-------------si possono eliminiare
void Keypoints_From_Filtered_Matches_Multiple(std::vector<std::vector<cv::DMatch>> filtered_matches,
	std::vector<cv::KeyPoint> keypoints_image, cv::Mat image, std::vector<std::vector<cv::KeyPoint>> &keypoints_match);

void Keypoints_From_Filtered_Matches(std::vector<cv::DMatch> filtered_matches, std::vector<cv::KeyPoint> keypoints_image, cv::Mat image, std::vector<cv::KeyPoint> &keypoints_match);
//--------------------