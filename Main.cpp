#include "Keypoint_Detection.h"
#include "Keypoint_Descriptor.h"
#include "Descriptor_Matching.h"
#include "Homography.h"
#define VISUALIZE_EVERYTHING = true; 



int main(int argc, char**argv){

//-------------------------TASK A--------------------------------------------------
	/*
#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
	cv::initModule_nonfree();
#endif

	
	cv::Mat model_1 = cv::imread("../models/0.jpg");
	cv::Mat model_2 = cv::imread("../models/26.jpg");
	cv::Mat model_3 = cv::imread("../models/25.jpg");
	cv::Mat model_4 = cv::imread("../models/11.jpg");
	cv::Mat scene = cv::imread("../scenes/e4.png");
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

		std::vector<cv::KeyPoint> keypoints_model_1, keypoints_model_2, keypoints_model_3, keypoints_model_4, keypoints_scene;
	
	Keypoint_Detection(model_1, detector, keypoints_model_1);
	Keypoint_Detection(model_2, detector, keypoints_model_2);
	Keypoint_Detection(model_3, detector, keypoints_model_3);
	Keypoint_Detection(model_4, detector, keypoints_model_4);
	Keypoint_Detection(scene, detector, keypoints_scene);

	cv::Mat descriptor_model_1, descriptor_model_2, descriptor_model_3, descriptor_model_4, descriptor_scene;

	Keypoint_Descriptor(model_1, keypoints_model_1, descriptor, descriptor_model_1);
	Keypoint_Descriptor(model_2, keypoints_model_2, descriptor, descriptor_model_2);
	Keypoint_Descriptor(model_3, keypoints_model_3, descriptor, descriptor_model_3);
	Keypoint_Descriptor(model_4, keypoints_model_4, descriptor, descriptor_model_4);
	Keypoint_Descriptor(scene, keypoints_scene, descriptor, descriptor_scene);

	#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
		cv::Ptr<cv::DescriptorMatcher> matcher_1 = cv::DescriptorMatcher::create("FlannBased");
		cv::Ptr<cv::DescriptorMatcher> matcher_2 = cv::DescriptorMatcher::create("FlannBased");
		cv::Ptr<cv::DescriptorMatcher> matcher_3 = cv::DescriptorMatcher::create("FlannBased");
		cv::Ptr<cv::DescriptorMatcher> matcher_4 = cv::DescriptorMatcher::create("FlannBased");
	#else
		cv::Ptr<cv::DescriptorMatcher> matcher = cv::makePtr<cv::FlannBasedMatcher>(new cv::flann::LshIndexParams(10, 20, 2));
	#endif

		std::vector<cv::DMatch> filtered_match_1, filtered_match_2, filtered_match_3, filtered_match_4;
		std::vector<cv::DMatch> all_match_1, all_match_2, all_match_3, all_match_4;
	
	Descriptor_Matching(model_1, scene, descriptor_model_1, descriptor_scene, keypoints_model_1, keypoints_scene, matcher_1, filtered_match_1, all_match_1);
	
	Descriptor_Matching(model_2, scene, descriptor_model_2, descriptor_scene, keypoints_model_2, keypoints_scene, matcher_2, filtered_match_2, all_match_2);
	
	Descriptor_Matching(model_3, scene, descriptor_model_3, descriptor_scene, keypoints_model_3, keypoints_scene, matcher_3, filtered_match_3, all_match_3);
	
	Descriptor_Matching(model_4, scene, descriptor_model_4, descriptor_scene, keypoints_model_4, keypoints_scene, matcher_4, filtered_match_4, all_match_4);

	//Homography(model_1, scene, keypoints_model_1, keypoints_scene, filtered_match_1);
	
	//Homography(model_2, scene, keypoints_model_2, keypoints_scene, filtered_match_2);

	//Homography(model_3, scene, keypoints_model_3, keypoints_scene, filtered_match_3);
	
	
	
	std::vector<cv::Mat> models = { model_1, model_2, model_3, model_4 };
	std::vector<std::vector<cv::DMatch>> filtered_matches = { filtered_match_1, filtered_match_2, filtered_match_3, filtered_match_4 };
	std::vector<std::vector<cv::KeyPoint>> keypoints_models = { keypoints_model_1, keypoints_model_2, keypoints_model_3, keypoints_model_4 };
	
	Multi_Homography(scene, keypoints_scene, models, filtered_matches, keypoints_models);

	*/

//-------------------------TASK B--------------------------------------------------

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
	cv::initModule_nonfree();
#endif
	
	cv::Mat src = cv::imread("../models/0.jpg");
	cv::Mat dst;
	cv::RNG rng(12345);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::namedWindow("Source", cv::WINDOW_AUTOSIZE);
	cv::imshow("Source", src);

	Canny(src, dst, 50, 200, 3); 

	cv::namedWindow("Canny", cv::WINDOW_NORMAL);
	cv::imshow("Canny", dst);


	// trova i contorni
	cv::findContours(dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	
	//trova i momenti
	std::vector<cv::Moments> moments(contours.size());
	
	for (int i = 0; i < contours.size(); i++){
		moments[i] = cv::moments(contours[i], false);
	}

	//trova per ogni punto del contorno il baricentro
	std::vector<cv::Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = cv::Point2f(moments[i].m10 / moments[i].m00, moments[i].m01 / moments[i].m00);
	}
	 
	// disegna i contorni
	cv::Mat drawing = cv::Mat::zeros(dst.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
		
		//disegna i baricentri
		circle(drawing, mc[i], 7, color, -1, 8, 0);
		

	//	putText(drawing, "center", mc[i], cv::FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2);
	}

	cv::namedWindow("conoturs", cv::WINDOW_NORMAL);
	cv::imshow("conoturs", drawing);


// stampa a video -----------------------------------------------------
	printf("\t Info: Area and Contour Length \n");
	for (size_t i = 0; i< contours.size(); i++)
	{
		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", (int)i, moments[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0,cv::Point());
		
	}
//----------------------------------------------------------------------
	
	// GRADIENTI
	int ddepth = CV_16S;
	int scale = 1;
	int delta = 0;
	cv::Mat src_gray;
	cv::GaussianBlur(src, dst, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	//bianco e nero
	cv::cvtColor(src, src_gray, CV_BGR2GRAY);
	cv::Mat grad_wind;

	cv::Mat grad_x, grad_y, abs_grad_x, abs_grad_y;

	//gradiente di x
	
  //Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT);
	Scharr(src_gray, grad_x, ddepth, 1, 0, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(grad_x, abs_grad_x);

	//gradiente di y
  //Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
	Scharr(src_gray, grad_y, ddepth, 0, 1, scale, delta, cv::BORDER_DEFAULT);
	cv::convertScaleAbs(grad_y, abs_grad_y);
	
	//gradiente totale approssimato
	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad_wind);




	cv::imshow("gradiente", grad_wind);

	

	//------------------------------------------------------------------------
	cvWaitKey();

}