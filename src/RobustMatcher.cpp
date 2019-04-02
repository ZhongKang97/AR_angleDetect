#include"../include/RobustMatcher.h"
RobustMatcher::~RobustMatcher()
{
}
cv::Mat RobustMatcher::match(cv::Mat &image1, cv::Mat &image2,
	std::vector<cv::DMatch>& matches,//���ƥ����
	std::vector<cv::KeyPoint>& keypoints1,//����ؼ���
	std::vector<cv::KeyPoint> & keypoints2)
{
	//���������
	detector->detect(image1, keypoints1);
	detector->detect(image2, keypoints2);
	//��ȡ����������
	cv::Mat descriptors1, descriptors2;
	descriptor->compute(image1, keypoints1, descriptors1);
	descriptor->compute(image2, keypoints2, descriptors2);
	//ƥ��������
	cv::BFMatcher matcher(normType, true);
	std::vector<cv::DMatch> outputMatches;
	matcher.match(descriptors1, descriptors2, outputMatches);
	//��RANSAC�㷨�Ż�ƥ����
	cv::Mat fundmental = ransacTest(outputMatches, keypoints1, keypoints2, matches);
	return fundmental;
}
/*********************Sample***************/
/*
int main()
{
	Mat image1, image2;
	//׼��ƥ���� ʹ��SIFT�������������
	RobustMatcher rmatcher(cv::xfeatures2d::SIFT::create(250));
	//ƥ������ͼ��
	std::vector<cv::DMatch> matches;
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Mat fundmental = rmatcher.match(image1, image2, matches, keypoints1, keypoints2);
}
*/