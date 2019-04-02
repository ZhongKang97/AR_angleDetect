#ifndef ROBUSTMATHCER_H
#define ROBUSTMATHCER_H
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/features2d.hpp>
#include"180923_ransactest.h"
class RobustMatcher
{
public:
	RobustMatcher(const cv::Ptr<cv::FeatureDetector> &detector,
		const cv::Ptr<cv::DescriptorExtractor>& descriptor = cv::Ptr<cv::DescriptorExtractor>()) :
		detector(detector), descriptor(descriptor),
		normType(cv::NORM_L2), ratio(0.8f),
		estimateF(true), estimateM(true),
		confidence(0.98), distance(1.0)
	{
		if (!this->descriptor)
			this->descriptor = this->detector;
	}
	~RobustMatcher();
	cv::Mat match(cv::Mat &image1, cv::Mat &image2,
		std::vector<cv::DMatch>& matches,
		std::vector<cv::KeyPoint>& keypoints1,
		std::vector<cv::KeyPoint> & keypoints2);
	void setNormType(int type) { normType = type; }
private:
	cv::Ptr<cv::FeatureDetector> detector;
	cv::Ptr<cv::DescriptorExtractor> descriptor;
	int normType;
	float ratio; //第一个和第一个NN之间的最大比率
	bool estimateF; //是否优化基础矩阵
	bool estimateM;//是否优化匹配结果
	double distance; //到极点的最小距离
	double confidence;//置信度
};
#endif // !ROBUSTMATHCER_H
