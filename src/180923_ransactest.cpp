#include"../include/180923_ransactest.h"
Mat ransacTest(const vector<DMatch>&matches,
	vector<KeyPoint> &KPS1,
	vector<KeyPoint>&KPS2,
	vector<DMatch> &outMatches)
{
	outMatches.clear();
	double distance = 1.0, confidence = 0.98;
	vector<Point2f> Pt1, Pt2;
	for (vector<DMatch>::const_iterator it = matches.begin(); it != matches.end(); it++)
	{
		Pt1.push_back(KPS1[it->queryIdx].pt);
		Pt2.push_back(KPS2[it->trainIdx].pt);
	}
	vector<uchar> inliers(Pt1.size(), 0);
	Mat fundamental = findFundamentalMat(Pt1, Pt2,
		FM_RANSAC,
		distance,//到对极线的距离
		confidence);//置信度
	vector<Point2f> newPt1, newPt2;
	correctMatches(fundamental, Pt1, Pt2, newPt1, newPt2);
	fundamental = findFundamentalMat(newPt1, newPt2,
		inliers,//匹配状态
		FM_RANSAC,
		distance,//到对极线的距离
		confidence);//置信度
	vector<uchar>::const_iterator itIn = inliers.begin();
	vector<DMatch>::const_iterator itM = matches.begin();
	for (; itIn != inliers.end(); itIn++, itM++)//遍历所有匹配项，获取优质匹配项
	{
		if (*itIn) outMatches.push_back(*itM);
	}
	return fundamental;
}
Mat ransacTest_Homo(const vector<DMatch>&matches,
	vector<KeyPoint> &KPS1,
	vector<KeyPoint>&KPS2,
	vector<DMatch> &outMatches)
{
	outMatches.clear();
	double distance = 1.0, confidence = 0.98;
	vector<Point2f> Pt1, Pt2;
	for (vector<DMatch>::const_iterator it = matches.begin(); it != matches.end(); it++)
	{
		Pt1.push_back(KPS1[it->queryIdx].pt);
		Pt2.push_back(KPS2[it->trainIdx].pt);
	}
	vector<uchar> inliers(Pt1.size(), 0);
	Mat Homo = findHomography(Pt1, Pt2,
		inliers,//匹配状态
		RANSAC,
		distance);//到对极线的距离
	vector<uchar>::const_iterator itIn = inliers.begin();
	vector<DMatch>::const_iterator itM = matches.begin();
	for (; itIn != inliers.end(); itIn++, itM++)//遍历所有匹配项，获取优质匹配项
	{
		if (*itIn) outMatches.push_back(*itM);
	}
	return Homo;
}