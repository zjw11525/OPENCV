#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	Mat src = imread("2.jpg");
	imshow("src", src);
	Mat dst;
	//上采样
	//pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
	//imshow("pyrUp", dst);
	////降采样
	//pyrDown(src, dst, Size(src.cols / 2, src.rows / 2));
	//imshow("pyrUp", dst);

	//DOG 高斯不同 
	Mat gray,g1,g2,dogimage;
	cvtColor(src, gray, CV_BGR2GRAY);
	GaussianBlur(gray, g1,Size(5,5),0,0);
	GaussianBlur(g1, g2, Size(5, 5), 0, 0);
	subtract(g2, g1, dogimage,Mat());
	
	
	//归一化显示
	normalize(dogimage,dogimage,255,0,NORM_MINMAX);
	imshow("dogimage", dogimage);
	waitKey(0);
	return 0;
}