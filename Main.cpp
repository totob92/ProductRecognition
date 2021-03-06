#include "Keypoint_Detection.h"
#include "Keypoint_Descriptor.h"
#include "Descriptor_Matching.h"
#include "Homography.h"
#include "Box.h"
extern bool VISUALIZE_EVERYTHING = false;





int main(int argc, char**argv){

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
	cv::initModule_nonfree();
#endif
	
	
	//task c

	cv::Mat model_1 = cv::imread("../models/3.jpg");
	cv::Mat model_2 = cv::imread("../models/11.jpg");
	cv::Mat model_3 = cv::imread("../models/26.jpg");
	cv::Mat scene = cv::imread("../scenes/h2.jpg");

	int epsilon = 10; 
	int minPoints = 15; 
	

	/*
	//task b

	cv::Mat model_1 = cv::imread("../models/26.jpg");
	cv::Mat model_2 = cv::imread("../models/25.jpg");
	cv::Mat model_3 = cv::imread("../models/19.jpg");
	cv::Mat scene = cv::imread("../scenes/m3.png");

	int epsilon = 100; 
	int minPoints = 160; 
	*/

	/*
	//task a

	cv::Mat model_1 = cv::imread("../models/24.jpg");
	cv::Mat model_2 = cv::imread("../models/26.jpg");
	cv::Mat model_3 = cv::imread("../models/25.jpg");
	cv::Mat scene = cv::imread("../scenes/e2.png");

	
	int epsilon = 100;
	int minPoints = 160;
	*/
	

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
	cv::Ptr<cv::Feature2D> detector = cv::Feature2D::create("SIFT");
	cv::Ptr<cv::Feature2D> descriptor = cv::Feature2D::create("SIFT");
#else
	cv::Ptr<cv::Feature2D> detector = cv::BRISK::create();
	cv::Ptr<cv::Feature2D> descriptor = cv::BRISK::create();
#endif

	std::vector<cv::KeyPoint> keypoints_model_1, keypoints_model_2, keypoints_model_3, keypoints_scene;

	cv::Mat descriptor_model_1, descriptor_model_2, descriptor_model_3, descriptor_scene;

	std::vector<cv::Mat> models;
	models.push_back(model_1);
	models.push_back(model_2);
	models.push_back(model_3);

	std::vector<std::vector<cv::KeyPoint>> keyPoint_models;
	keyPoint_models.push_back(keypoints_model_1);
	keyPoint_models.push_back(keypoints_model_2);
	keyPoint_models.push_back(keypoints_model_3);

	std::vector<cv::Mat> descriptor_models;
	descriptor_models.push_back(descriptor_model_1);
	descriptor_models.push_back(descriptor_model_2);
	descriptor_models.push_back(descriptor_model_3);

	Keypoint_Detection_Multiple(models, detector, keyPoint_models);
	Keypoint_Detection(scene, detector, keypoints_scene);


	Keypoint_Descriptor_Multiple(models, keyPoint_models, descriptor, descriptor_models);
	Keypoint_Descriptor(scene, keypoints_scene, descriptor, descriptor_scene);

	#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
		cv::Ptr<cv::DescriptorMatcher> matcher_1 = cv::DescriptorMatcher::create("FlannBased");
		cv::Ptr<cv::DescriptorMatcher> matcher_2 = cv::DescriptorMatcher::create("FlannBased");
		cv::Ptr<cv::DescriptorMatcher> matcher_3 = cv::DescriptorMatcher::create("FlannBased");
	#else
		cv::Ptr<cv::DescriptorMatcher> matcher = cv::makePtr<cv::FlannBasedMatcher>(new cv::flann::LshIndexParams(10, 20, 2));
	#endif

	std::vector<cv::DMatch> filtered_match_1, filtered_match_2, filtered_match_3;
	std::vector<cv::DMatch> all_match_1, all_match_2, all_match_3;

	std::vector<cv::Ptr<cv::DescriptorMatcher>> matchers;
	matchers.push_back(matcher_1);
	matchers.push_back(matcher_2);
	matchers.push_back(matcher_3);

	std::vector<std::vector<cv::DMatch>> filtered_matches;
	filtered_matches.push_back(filtered_match_1);
	filtered_matches.push_back(filtered_match_2);
	filtered_matches.push_back(filtered_match_3);


	std::vector<std::vector<cv::DMatch>> all_matches;
	all_matches.push_back(all_match_1);
	all_matches.push_back(all_match_2);
	all_matches.push_back(all_match_3);

	Descriptor_Matching_Multiple(models, scene, descriptor_models, descriptor_scene, keyPoint_models, keypoints_scene, matchers, filtered_matches, all_matches);
	

//-------------------------TASK A--------------------------------------------------
	/*
	Multi_Homography(scene, keypoints_scene, models, filtered_matches, keyPoint_models);
	*/


//-------------------------TASK B--------------------------------------------------
	
	std::vector<Centers_From_KeyPoints> corrispondenze;

	corrispondenze = get_Centers_Multiple(models, filtered_matches, keyPoint_models, keypoints_scene, scene);
	
	std::vector<std::vector<Centers_From_KeyPoints>> corrispondenze_plus = DBSCAN_Centers_Multiple(scene, corrispondenze, epsilon, minPoints);
	
	Multi_MyHomography(models, scene, corrispondenze_plus);
	

}