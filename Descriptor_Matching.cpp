#include "Descriptor_Matching.h"

void Descriptor_Matching(cv::Mat model, cv::Mat scene, cv::Mat descriptor_model, cv::Mat descriptor_scene, std::vector<cv::KeyPoint> keypoints_model,
	std::vector<cv::KeyPoint> keypoints_scene, cv::Ptr<cv::DescriptorMatcher> &matcher, std::vector<cv::DMatch> &filtered_match, std::vector<cv::DMatch> &all_match){

	bool visualize_everything = true;

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

	if (VISUALIZE_EVERYTHING==true){
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

//-----------------si possono eliminare
void Keypoints_From_Filtered_Matches(std::vector<cv::DMatch> filtered_matches, std::vector<cv::KeyPoint> keypoints_image, cv::Mat image, std::vector<cv::KeyPoint> &keypoints_match){

	cv::Mat target_copy;

	for (int i = 0; i < filtered_matches.size(); i++){
		int temp = filtered_matches.at(i).queryIdx;
		keypoints_match.push_back(keypoints_image.at(temp));
	}

	if (VISUALIZE_EVERYTHING == true){
		cv::drawKeypoints(image, keypoints_match, target_copy, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::namedWindow("Keypoint Matching", cv::WINDOW_NORMAL);
		cv::imshow("Keypoint Matching", target_copy);
		cv::waitKey();
		cv::destroyAllWindows();
	}
}

void Keypoints_From_Filtered_Matches_Multiple(std::vector<std::vector<cv::DMatch>> filtered_matches, 
	std::vector<cv::KeyPoint> keypoints_image, cv::Mat image, std::vector<std::vector<cv::KeyPoint>> &keypoints_match){


	cv::Mat target_copy;
	image.copyTo(target_copy);

	for (int i = 0; i < filtered_matches.size(); i++){

		for (int j = 0; j < filtered_matches.at(i).size(); j++){
			std::vector<cv::DMatch> temp = filtered_matches.at(i);
			int temp_bis = temp.at(j).queryIdx;
			keypoints_match.at(i).push_back(keypoints_image.at(temp_bis));
		}

		cv::drawKeypoints(image, keypoints_match.at(i), target_copy, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	}
	if (VISUALIZE_EVERYTHING == true){

		cv::namedWindow("Keypoint_Matching", cv::WINDOW_NORMAL);
		cv::imshow("Keypoint_Matching", target_copy);
		cv::waitKey();

	}

}
//---------------

void Descriptor_Matching_Multiple(std::vector<cv::Mat> models, cv::Mat scene, std::vector<cv::Mat>descriptor_models, cv::Mat descriptor_scene, std::vector<std::vector<cv::KeyPoint>> keypoints_models,
	std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::Ptr<cv::DescriptorMatcher>> &matchers, std::vector<std::vector<cv::DMatch>> &filtered_matches, std::vector<std::vector<cv::DMatch>> &all_matches){
	
	for (int j = 0; j < models.size(); j++){

		cv::Mat model = models.at(j);
		cv::Mat descriptor_model = descriptor_models.at(j);
		cv::Ptr<cv::DescriptorMatcher> matcher = matchers.at(j);
		std::vector<cv::KeyPoint> keypoints_model = keypoints_models.at(j);
		std::vector<cv::DMatch> filtered_match = filtered_matches.at(j);
		std::vector<cv::DMatch> all_match = all_matches.at(j);

		std::vector<cv::Mat> models_descriptors;
		models_descriptors.push_back(descriptor_model);
		//add model descriptor
		matcher->add(models_descriptors);

		//matching
		std::vector<std::vector<cv::DMatch>> matches;
		matcher->knnMatch(descriptor_scene, matches, 2);
		std::cout << matches.size() << " match founded on image "<< j+1 << std::endl;

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
		filtered_matches.at(j) = filtered_match;

		if (VISUALIZE_EVERYTHING==true){
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
}