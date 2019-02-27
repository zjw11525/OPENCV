#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	//Mat src(600,600,CV_8UC3,Scalar(0,255,0));
	Mat src = imread("2.jpg");
	imshow("src",src);

	Mat gray;
	cvtColor(src,gray,CV_BGR2GRAY);
	imshow("gray", gray);

	Mat binary;
	adaptiveThreshold(~gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,15,-2);
	imshow("binary", binary);

	//水平结构元素
	Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
	//垂直结构元素
	Mat vline = getStructuringElement(MORPH_RECT, Size(1 ,src.rows / 16), Point(-1, -1));
	//矩形结构
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	Mat dst,temp;
	morphologyEx(binary,dst,CV_MOP_OPEN,kernel,Point(-1,-1));
	//erode(binary, temp, hline);//开操作 = 腐蚀后膨胀
	//dilate(temp, dst, hline);

	bitwise_not(dst,dst);
	//blur(dst,dst,Size(3,3),Point(-1,-1));
	imshow("dst",dst);

	waitKey(0);
	return 0;
}