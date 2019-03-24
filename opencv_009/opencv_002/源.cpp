#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;
Mat MyLines(Mat image);
Mat MyRect(Mat image);
Mat Myellipse(Mat image);
Mat MyCircle(Mat image);
Mat MyPolygon(Mat image);
void RandomLine(Mat image);
Mat frame;
Mat dst;
int sigma = 50;
void blur(int, void*) 
{
	bilateralFilter(frame, dst, 15, sigma, 5);//Ë«±ßÂË²¨
	Mat kernel = (Mat_<int>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
	filter2D(dst,dst,-1,kernel,Point(-1,-1),0);
	GaussianBlur(dst,dst,Size(11,11),11,11);//size±ØÐëÈ¡ÆæÊý
	imshow("dst", dst);
}
int main(int argc, char** argv) {
	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	while (1) 
	{
		cap >> frame;
		imshow("dst", frame);

		createTrackbar("d", "dst", &sigma, 100, blur);
		blur(0, 0);
		//Mat dst = Mat::zeros(src.size(),src.type());
		//Mat dst1 = Mat::zeros(src.size(), src.type());
		//medianBlur(src,dst,3);
		//bilateralFilter(frame,dst,15,50,5);//Ë«±ßÂË²¨
		//blur(src,dst,Size(11,11),Point(-1,-1));

		//imshow("dst",dst);

		//Mat kernel = (Mat_<int>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
		//filter2D(dst,dst1,-1,kernel,Point(-1,-1),0);
		////GaussianBlur(src,dst1,Size(11,11),11,11);//size±ØÐëÈ¡ÆæÊý
		//imshow("dst1",dst1);


		if (waitKey(50) == 27)
			break;
	}
	//Mat src = imread("22.jpg");
	//if (!src.data) {
	//	return -1;
	//}
	//imshow("src",src);



	waitKey(0);
	return 0;
}
Mat MyLines(Mat image)
{
	Point p1 = Point(20,30);
	Point p2;
	p2.x = 300;
	p2.y = 300;
	Scalar color = Scalar(0,0,255);
	line(image,p1,p2,color,1,LINE_AA);
	return image;
}
Mat MyRect(Mat image)
{
	Rect r = Rect(100,100,100,100); 
	Scalar color = Scalar(0, 255, 0);
	rectangle(image,r,color,1,LINE_8);
	return image;
}
Mat Myellipse(Mat image) {
	Scalar color = Scalar(0,255,0);

	ellipse(image,Point(200,200),Size(20,30),45,0,360,color,1,LINE_8);
	return image;
}

Mat MyCircle(Mat image) {
	Scalar color = Scalar(0, 255, 0);
	Point center = Point(image.rows/2,image.cols/2);
	circle(image,center,50,color,2,LINE_8);
	
	return image;
}
Mat MyPolygon(Mat image) {
	Point pts[1][5];
	pts[0][0] = Point(0, 0);
	pts[0][1] = Point(0, 100);
	pts[0][2] = Point(100, 100);
	pts[0][3] = Point(100, 0);
	//pts[0][4] = Point(0, 100);
	const Point* ppts[] = { pts[0] };
	int npt[] = { 4 };
	Scalar color = Scalar(0, 255, 0);
	fillPoly(image, ppts, npt, 1, color, LINE_8);
	return image;
}
void RandomLine(Mat image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	RNG rng = RNG(12345);
	Point p1, p2;
	while (1) {
	p1.x = rng.uniform(0, image.cols);
	p1.y = rng.uniform(0, image.rows);
	p2.x = rng.uniform(0, image.cols);
	p2.y = rng.uniform(0, image.rows);
	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	line(dst, p1, p2, color, 1, LINE_8);
	imshow("dst", dst);
	if (waitKey(50) > 0) { break; }
	}
}