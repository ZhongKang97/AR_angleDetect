#ifndef _180923_RANSACTEST_H
#define _180923_RANSACTEST_H
#include"opencv2/opencv.hpp"
using namespace cv;
using namespace std;
Mat ransacTest(const vector<DMatch>&matches,
               vector<KeyPoint> &KPS1,
               vector<KeyPoint>&KPS2,
               vector<DMatch> &outMatches);
Mat ransacTest_Homo(const vector<DMatch>&matches,
               vector<KeyPoint> &KPS1,
               vector<KeyPoint>&KPS2,
               vector<DMatch> &outMatches);
#endif // 180923_RANSACTEST_H
