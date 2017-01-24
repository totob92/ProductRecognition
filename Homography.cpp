#include "Homography.h"
#include "Box.h"

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


	//---------------------------------------------------------------------------------------------------------------------
	
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
	

	//---------------------------------------------------------------------------------------------------------------------

	

}

void Multi_Homography(cv::Mat scene, std::vector<cv::KeyPoint> keypoints_scene, std::vector<cv::Mat> models, std::vector<std::vector<cv::DMatch>> filtered_matches,std::vector<std::vector<cv::KeyPoint>> keypoints_models
	)
{
	std::vector<cv::Point2d> model_points;
	std::vector<cv::Point2d> scene_points;
	cv::Mat bounding_box;
	std::vector<Box> box_obj_corners(3); 
	std::vector<Box> box_scene_corners(3);

	for (int i = 0; i < filtered_matches.size(); i++){
		std::vector<cv::DMatch> current_filterd = filtered_matches[i];
		cv::Mat current_model = models[i];
		std::vector<cv::KeyPoint> current_keypoint_model = keypoints_models[i];

		for (int j = 0; j < current_filterd.size(); j++){
			cv::DMatch current = current_filterd[j];
			model_points.push_back(current_keypoint_model[current.trainIdx].pt);
			scene_points.push_back(keypoints_scene[current.queryIdx].pt);
		}
		

		//estimate homography using ransac
		cv::Mat homography = cv::findHomography(model_points, scene_points, CV_RANSAC);
		std::cout << "Homography estimated" << std::endl;
		
		scene.copyTo(bounding_box);



		//compute scene bounding box corner using the homography computed right now
		
		box_obj_corners[i].point0 = cv::Point(0, 0);
		box_obj_corners[i].point1 = cv::Point(current_model.cols, 0);
		box_obj_corners[i].point2 = cv::Point(current_model.cols, current_model.rows);
		box_obj_corners[i].point3 = cv::Point(0, current_model.rows);
		
		perspectiveTransform(box_obj_corners[i].toVector(), box_scene_corners[i].toVector(), homography);


		

	}
	
	//draw the bounding box
	box_scene_corners[0].drawYourself(bounding_box, cv::Scalar(0,255,0),6);
	box_scene_corners[1].drawYourself(bounding_box, cv::Scalar(255, 0, 0), 6);
	box_scene_corners[2].drawYourself(bounding_box, cv::Scalar(255, 255, 255), 6);
		
	cv::namedWindow("Bounding box", cv::WINDOW_NORMAL);
	cv::imshow("Bounding box", bounding_box);
	cv::waitKey();
	cv::destroyAllWindows();
	
}