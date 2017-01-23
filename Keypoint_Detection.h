#include "opencv2/opencv.hpp"

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2) //opencv version 2.4.x
#include "opencv2/nonfree/nonfree.hpp"
#else  //opencv version 3.x
//to support SIFT and sURF in version 3 compile from source :(
#endif

void Keypoint_Detection(cv::Mat image, cv::Ptr<cv::Feature2D> detector, std::vector<cv::KeyPoint> &keypoints_image);