#include "opencv2/opencv.hpp"

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2) //opencv version 2.4.x
#include "opencv2/nonfree/nonfree.hpp"
#else  //opencv version 3.x
//to support SIFT and sURF in version 3 compile from source :(
#endif

void Keypoint_Descriptor(cv::Mat image, std::vector<cv::KeyPoint> keypoints_image, cv::Ptr<cv::Feature2D> descriptor, cv::Mat &descriptor_image);
