#include"../include/AR_poseAngleDetect.h"
int main(int argc, char** argv)
{
	AR_poseAngleDetector detector;
	cv::String xml_path = "D:/CODEing/OpenCV_codeSources/CameraCalibrate/C930E_640x480/";
	cv::String filename = "C930E_640x480_calibMatrixs.xml";
	detector.loadCameraMatrixFormXML(xml_path + filename);
	VideoCapture cap(1);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	if (cap.isOpened())
	{
		Mat KeyFrame, nowFrame;
		Mat rotationMatrix, transposeMatrix;
		bool init = true;
		while (true)
		{
			if (init)
			{
				cap >> KeyFrame;
				if (KeyFrame.empty()) break;
				nowFrame = KeyFrame.clone();
				init = false;
			}
			else cap >> nowFrame;
			if (nowFrame.empty()) break;
			if (detector.detect(KeyFrame, nowFrame, rotationMatrix, transposeMatrix))
			{
				Mat rv;
				Rodrigues(rotationMatrix, rv);
				rv *= 90;
				//cout << "绕相机X轴旋转： " << rv.at<double>(0,0) << "°"<< endl;
				//cout << "绕相机Y轴旋转： " << rv.at<double>(1, 0) <<"°"<< endl;
				cout << "绕相机Z轴旋转： " << rv.at<double>(2, 0) <<"°" << endl;
				int font_face = cv::FONT_HERSHEY_COMPLEX;//字体 
				double font_scale = 1;//字体大小
				int thickness = 1;//线宽
				std::string text = format("Ang: %f deg", rv.at<double>(2, 0));
				putText(nowFrame, text, Point(0, 40), font_face, font_scale, Scalar(0, 125, 255), thickness, 8, 0);
				imshow("nowFrame", nowFrame);
			}		
			char c=waitKey(1);
			if (c == 27) break;
			if (c == 'k') KeyFrame = nowFrame.clone();
			
		}
	}
}