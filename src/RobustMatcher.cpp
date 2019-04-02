#include"../include/RobustMatcher.h"
RobustMatcher::~RobustMatcher()
{
}
cv::Mat RobustMatcher::match(cv::Mat &image1, cv::Mat &image2,
	std::vector<cv::DMatch>& matches,//输出匹配项
	std::vector<cv::KeyPoint>& keypoints1,//输出关键点
	std::vector<cv::KeyPoint> & keypoints2)
{
	//检测特征点
	detector->detect(image1, keypoints1);
	detector->detect(image2, keypoints2);
	//提取特征描述子
	cv::Mat descriptors1, descriptors2;
	descriptor->compute(image1, keypoints1, descriptors1);
	descriptor->compute(image2, keypoints2, descriptors2);
	//匹配描述子
	cv::BFMatcher matcher(normType, true);
	std::vector<cv::DMatch> outputMatches;
	matcher.match(descriptors1, descriptors2, outputMatches);
	//用RANSAC算法优化匹配项
	cv::Mat fundmental = ransacTest(outputMatches, keypoints1, keypoints2, matches);
	return fundmental;
}
/*********************Sample***************/
/*
int main()
{
	Mat image1, image2;
	//准备匹配器 使用SIFT检测器和描述子
	RobustMatcher rmatcher(cv::xfeatures2d::SIFT::create(250));
	//匹配两幅图像
	std::vector<cv::DMatch> matches;
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Mat fundmental = rmatcher.match(image1, image2, matches, keypoints1, keypoints2);
}
*/