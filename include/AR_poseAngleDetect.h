#ifndef AR_POSEANGLEDETECT_H
#define AR_POSEANGLEDETECT_H
#include<opencv2\opencv.hpp>
#include<iostream>
#include"RobustMatcher.h"
class AR_poseAngleDetector
{
public:
	AR_poseAngleDetector();
	~AR_poseAngleDetector();
	void loadCameraMatrixFormXML(cv::String filename);
	bool detect(cv::Mat img1, cv::Mat img2, cv::Mat& outR, cv::Mat& outT);
private:
	cv::Point2d pixel2cam(const Point2d& p);
	cv::Mat cameraMatrix;
};


#endif // !AR_POSEANGLEDETECT_H