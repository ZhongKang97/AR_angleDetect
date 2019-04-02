#include"../include/AR_poseAngleDetect.h"
#include"../include/RobustMatcher.h"
AR_poseAngleDetector::AR_poseAngleDetector()
{
}

AR_poseAngleDetector::~AR_poseAngleDetector()
{
}
/******************************/
//@������loadCameraMatrixFormXML
//@���ܣ��ӱ궨��xml�ļ���ȡ����ڲξ���
//@�������������·�����ļ���
/*****************************/
void AR_poseAngleDetector::loadCameraMatrixFormXML(cv::String filename)
{
	cout << "loading file from " << filename << endl;
	FileStorage file;
	file.open(filename, FileStorage::READ);
	file["CameraMatrix"] >> cameraMatrix;
	file.release();
	cout << "CameraMatrix: " << cameraMatrix << endl;
}
/******************************/
//@������pixel2cam
//@���ܣ��������������ϵת���������һ��ƽ������
//@�����������������ĵ�
/*****************************/
cv::Point2d AR_poseAngleDetector::pixel2cam(const Point2d& p)
{
	Mat k = cameraMatrix;
	return Point2d(
		(p.x - k.at<double>(0, 2)) / k.at<double>(0, 0),
		(p.y - k.at<double>(1, 2)) / k.at<double>(1, 1)
	);
}
/******************************/
//@������detect
//@���ܣ�������֡ͼ��֮�����ת�����Լ�ƽ��
//@�����������������ĵ�
/*****************************/
bool AR_poseAngleDetector::detect(cv::Mat img1, cv::Mat img2, cv::Mat& outR, cv::Mat& outT)
{
	Mat k = cameraMatrix;
	Mat fundmental_matrix;
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	std::vector<DMatch> matches;
	RobustMatcher rmatcher(cv::FastFeatureDetector::create(10),cv::BRISK::create());
	rmatcher.setNormType(cv::NORM_HAMMING);
	fundmental_matrix = rmatcher.match(img1, img2, matches, keypoints_1, keypoints_2);
	std::vector<Point2f> points1;
	std::vector<Point2f> points2;
	int length = (int)matches.size();
	for (int i = 0; i < length; i++)
	{
		points1.push_back(keypoints_1[matches[i].queryIdx].pt);
		points2.push_back(keypoints_2[matches[i].trainIdx].pt);
	}
	//cout << "Fundamental_matrix is :" << fundmental_matrix << endl;
	Mat essential_matrix;
	if (points1.size() > 8)
	{
		
		essential_matrix = cv::findEssentialMat(points1, points2, cameraMatrix);
		//cout << "Essential_matrix is : " << endl << essential_matrix << endl;
		recoverPose(essential_matrix, points1, points2, cameraMatrix, outR, outT);
		//cout << "R is " << endl << outR << endl;
		//cout << "t is " << endl << outT << endl;
		return true;
	}
	return false;
}