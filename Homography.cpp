#include "Homography.h"

void Homography(cv::Mat model, cv::Mat scene, std::vector<cv::KeyPoint> keypoints_model,
	std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::DMatch> filtered_match){

	std::vector<cv::Point2d> model_points;

	std::vector<cv::Point2d> scene_points;

	for (int j = 0; j < filtered_match.size(); j++){
		cv::DMatch current = filtered_match[j];
		model_points.push_back(keypoints_model[current.trainIdx].pt);
		scene_points.push_back(keypoints_scene[current.queryIdx].pt);
	}

	//estimate homography using ransac
	cv::Mat homography = cv::findHomography(model_points, scene_points, CV_RANSAC);
	std::cout << "Homography estimated" << std::endl;
	cv::Mat bounding_box;
	scene.copyTo(bounding_box);

	//compute scene bounding box corner using the homography computed right now
	std::vector<cv::Point2f> obj_corners(4);
	obj_corners[0] = cv::Point(0, 0);
	obj_corners[1] = cv::Point(model.cols, 0);
	obj_corners[2] = cv::Point(model.cols, model.rows);
	obj_corners[3] = cv::Point(0, model.rows);
	std::vector<cv::Point2f> scene_corners(4);
	perspectiveTransform(obj_corners, scene_corners, homography);
	//draw the bounding box
	cv::line(bounding_box, scene_corners[0], scene_corners[1], cv::Scalar(0, 255, 0), 6);
	cv::line(bounding_box, scene_corners[1], scene_corners[2], cv::Scalar(0, 255, 0), 6);
	cv::line(bounding_box, scene_corners[2], scene_corners[3], cv::Scalar(0, 255, 0), 6);
	cv::line(bounding_box, scene_corners[3], scene_corners[0], cv::Scalar(0, 255, 0), 6);

	cv::namedWindow("Bounding box", cv::WINDOW_NORMAL);
	cv::imshow("Bounding box", bounding_box);
	cv::waitKey();
	cv::destroyAllWindows();

}

void Multi_Homography(cv::Mat scene, std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::Mat> models, std::vector<std::vector<cv::DMatch>> filtered_matches,std::vector<std::vector<cv::KeyPoint>> keypoints_models
	)
{
	
}