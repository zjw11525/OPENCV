#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat MyRect(Mat image, int x, int y);
Mat MyPolygon(Mat image, int a, int b, int c, int d, Scalar color);

int main() {
	Mat image = imread("2.jpg");
	Mat src(500, 500, CV_8UC3, Scalar(0,0,0));
	Rect r = Rect(100,100,100,100);
	Scalar color = Scalar(255,255,255);
	//src = MyRect(src, 300, 300);
	//src = MyRect(src, 300, 100);
	src = MyPolygon(src, 300, 100, 5, 5, Scalar(255, 255, 255));
	src = MyPolygon(src, 300, 300, 5, 5, Scalar(255, 255, 255));

	src = MyPolygon(src,100,100,100,100,Scalar(255,255,255));
	src = MyPolygon(src, 150, 150, 5, 5, Scalar(0, 0, 0));
	imshow("src", src);
	Mat source = src.clone();


	Mat kernel = getStructuringElement(MORPH_RECT, Size(7,7),Point(-1,-1));
	//开运算
	morphologyEx(src,src,CV_MOP_OPEN,kernel);
	imshow("open",src);

	//Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(src, src, CV_MOP_CLOSE, kernel);
	imshow("close", src);

	//顶帽
	//morphologyEx(source, source, CV_MOP_TOPHAT, kernel);
	imshow("TOPHAT", source);
	//黑帽
	morphologyEx(source, source, CV_MOP_BLACKHAT, kernel);
	imshow("TOPHAT", source);

	//形态学梯度
	morphologyEx(image, image, CV_MOP_GRADIENT, kernel);
	imshow("meme",image);

	waitKey(0);
	return 0;
}

Mat MyRect(Mat image ,int x,int y)
{
	Rect r = Rect(x, y, 5, 5);
	Scalar color = Scalar(255, 255, 255);
	rectangle(image, r, color, 1, LINE_8);
	return image;
}

Mat MyPolygon(Mat image,int a,int b,int c,int d,Scalar color) {
	Point pts[1][5];
	pts[0][0] = Point(a, b);
	pts[0][1] = Point(a, b+d);
	pts[0][2] = Point(a+c, b+d);
	pts[0][3] = Point(a+c, b);
	const Point* ppts[] = { pts[0] };
	int npt[] = { 4 };
	fillPoly(image, ppts, npt, 1, color, LINE_8);
	return image;
}
