#include "Descriptor_Matching.h"

void Descriptor_Matching(cv::Mat model, cv::Mat scene, cv::Mat descriptor_model, cv::Mat descriptor_scene, std::vector<cv::KeyPoint> keypoints_model,
	std::vector<cv::KeyPoint> keypoints_scene, cv::Ptr<cv::DescriptorMatcher> &matcher, std::vector<cv::DMatch> &filtered_match, std::vector<cv::DMatch> &all_match){

	bool visualize_everything = false;

	std::vector<cv::Mat> models_descriptors;
	models_descriptors.push_back(descriptor_model);
	//add model descriptor
	matcher->add(models_descriptors);

	//matching
	std::vector<std::vector<cv::DMatch>> matches;
	matcher->knnMatch(descriptor_scene, matches, 2);
	std::cout << matches.size() << " match founded" << std::endl;

	//ratio test to discard bad matches

	float ratio_th = 0.8;
	for (int i = 0; i < matches.size(); i++){
		std::vector<cv::DMatch> current_match = matches[i];
		if (current_match.size() == 2){
			all_match.push_back(current_match[0]);
			if ((current_match[0].distance / current_match[1].distance) < ratio_th){
				filtered_match.push_back(current_match[0]);
			}
		}
	}
	std::cout << filtered_match.size() << " good match after ratio test" << std::endl;

	if (visualize_everything){
		//draw matches
		cv::Mat result_pre_filter, result;
		cv::drawMatches(scene, keypoints_scene, model, keypoints_model, all_match, result_pre_filter, cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		cv::drawMatches(scene, keypoints_scene, model, keypoints_model, filtered_match, result);
		cv::namedWindow("Not filtered", cv::WINDOW_NORMAL);
		cv::namedWindow("Filtered", cv::WINDOW_NORMAL);
		cv::imshow("Not filtered", result_pre_filter);
		cv::imshow("Filtered", result);
		cv::waitKey();
		cv::destroyAllWindows();
	}
	
}