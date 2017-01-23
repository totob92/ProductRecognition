#include "Keypoint_Detection.h"

void Keypoint_Detection(cv::Mat image, cv::Ptr<cv::Feature2D> detector, std::vector<cv::KeyPoint> &keypoints_image){
	bool visualize_everything = true;
	detector->detect(image, keypoints_image);
	std::cout << keypoints_image.size() << " Keypoints found on model" << std::endl;

	//DA TOGLIERE
	if (visualize_everything){
		//show detected keypoints
		cv::Mat target_copy, scene_copy;
		cv::drawKeypoints(image, keypoints_image, target_copy, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Model", target_copy);

		std::cout << "Keypoint detected" << std::endl;
		cv::waitKey();
		cv::destroyAllWindows();
	}
	
}