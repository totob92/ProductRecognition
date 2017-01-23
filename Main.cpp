#include "Keypoint_Detection.h"
#include "Keypoint_Descriptor.h"
#include "Descriptor_Matching.h"
#include "Homography.h"
#define VISUALIZE_EVERYTHING = true; 

int main(int argc, char**argv){

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
	cv::initModule_nonfree();
#endif

	
	cv::Mat model_1 = cv::imread("C:/Users/arman/Desktop/Progetto_CV/models/0.jpg");
	cv::Mat model_2 = cv::imread("C:/Users/arman/Desktop/Progetto_CV/models/1.jpg");
	cv::Mat model_3 = cv::imread("C:/Users/arman/Desktop/Progetto_CV/models/11.jpg");
	cv::Mat scene = cv::imread("C:/Users/arman/Desktop/Progetto_CV/scenes/e3.png");
	if (model_1.data == NULL || scene.data == NULL){
		std::cout << "Unable to load image..." << std::endl;
		std::exit(1);
	}
	std::cout << "Model Image loaded..." << std::endl;

	int max_keypoint = 1000;

	#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
		cv::Ptr<cv::Feature2D> detector = cv::Feature2D::create("SIFT");
		cv::Ptr<cv::Feature2D> descriptor = cv::Feature2D::create("SIFT");
	#else
		cv::Ptr<cv::Feature2D> detector = cv::BRISK::create();
		cv::Ptr<cv::Feature2D> descriptor = cv::BRISK::create();
	#endif

	std::vector<cv::KeyPoint> keypoints_model_1, keypoints_model_2, keypoints_model_3, keypoints_scene;
	
	Keypoint_Detection(model_1, detector, keypoints_model_1);
	Keypoint_Detection(model_2, detector, keypoints_model_2);
	Keypoint_Detection(model_3, detector, keypoints_model_3);
	Keypoint_Detection(scene, detector, keypoints_scene);

	cv::Mat descriptor_model_1, descriptor_model_2, descriptor_model_3, descriptor_scene;

	Keypoint_Descriptor(model_1, keypoints_model_1, descriptor, descriptor_model_1);
	Keypoint_Descriptor(model_2, keypoints_model_2, descriptor, descriptor_model_2);
	Keypoint_Descriptor(model_3, keypoints_model_3, descriptor, descriptor_model_3);
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
	
	Descriptor_Matching(model_1, scene, descriptor_model_1, descriptor_scene, keypoints_model_1, keypoints_scene, matcher_1, filtered_match_1, all_match_1);
	
	Descriptor_Matching(model_2, scene, descriptor_model_2, descriptor_scene, keypoints_model_2, keypoints_scene, matcher_2, filtered_match_2, all_match_2);
	
	Descriptor_Matching(model_3, scene, descriptor_model_3, descriptor_scene, keypoints_model_3, keypoints_scene, matcher_3, filtered_match_3, all_match_3);
	

	Homography(model_1, scene, keypoints_model_1, keypoints_scene, filtered_match_1);
	
	Homography(model_2, scene, keypoints_model_2, keypoints_scene, filtered_match_2);

	Homography(model_3, scene, keypoints_model_3, keypoints_scene, filtered_match_3);

	/*
	Commentato per la multiomografia
	std::vector<cv::Mat> models = { model_1, model_2, model_3 };
	std::vector<std::vector<cv::DMatch>> filtered_matches = { filtered_match_1, filtered_match_2, filtered_match_3 };
	std::vector<std::vector<cv::KeyPoint>> keypoints_models = { keypoints_model_1, keypoints_model_2, keypoints_model_3 };
	
	Multi_Homography(scene, keypoints_scene, models, filtered_matches, keypoints_models);*/

}