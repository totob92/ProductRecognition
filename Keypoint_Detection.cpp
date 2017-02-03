#include "Keypoint_Detection.h"

void Keypoint_Detection(cv::Mat image, cv::Ptr<cv::Feature2D> detector, std::vector<cv::KeyPoint> &keypoints_image){

	detector->detect(image, keypoints_image);
	
	std::cout << keypoints_image.size() << " Keypoints found on scene" << std::endl;

	if (VISUALIZE_EVERYTHING==true){
		//show detected keypoints
		cv::Mat target_copy, scene_copy;
		cv::drawKeypoints(image, keypoints_image, target_copy, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::namedWindow("Keypoint detected Image", cv::WINDOW_NORMAL);
		cv::imshow("Keypoint detected Image", target_copy);
		std::cout << "Keypoint detected" << std::endl;
		cv::waitKey();
		cv::destroyAllWindows();
	}
}

void Keypoint_Detection_Multiple(std::vector<cv::Mat> models, cv::Ptr<cv::Feature2D> detector, std::vector<std::vector<cv::KeyPoint>> &keypoints_image){

	for (int i = 0; i < models.size(); i++){

		detector->detect(models.at(i), keypoints_image.at(i));

		std::cout << keypoints_image.at(i).size() << " Keypoints found on image " << i + 1 << std::endl;

		if (VISUALIZE_EVERYTHING == true){
			//show detected keypoints
			cv::Mat target_copy, scene_copy;
			cv::drawKeypoints(models.at(i), keypoints_image.at(i), target_copy, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
			cv::namedWindow("Keypoint detected Image", cv::WINDOW_NORMAL);
			cv::imshow("Keypoint detected Image", target_copy);
			std::cout << "Keypoint detected" << std::endl;
			cv::waitKey();
			cv::destroyAllWindows();
		}
	}
}
