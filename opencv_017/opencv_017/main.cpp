#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() 
{
	Mat src = imread("1.jpg");
	imshow("src", src);
	Mat dst,gray;
	
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray, CV_BGR2GRAY);


	Mat xgrad;
	Mat ygrad;

	//Sobel(gray, xgrad, CV_16S, 1, 0, 3);
	//Sobel(gray, ygrad, CV_16S, 0, 1, 3);
	Scharr(gray, xgrad, CV_16S, 1, 0);
	Scharr(gray, ygrad, CV_16S, 0, 1);
	convertScaleAbs(xgrad, xgrad);
	convertScaleAbs(ygrad, ygrad);
	imshow("x", xgrad);
	imshow("y", ygrad);

	Mat xygrad;
	addWeighted(xgrad,0.5,ygrad,0.5,0,xygrad);
	imshow("xy", xygrad);

	waitKey(0);
	return 0;
}

//sobel是一阶微分，laplance是二阶微分