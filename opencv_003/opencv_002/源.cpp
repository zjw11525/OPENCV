#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src;
	src = imread("1.jpg");
	if (src.empty()) {
		cout << "could not load the image..." << endl;
		return -1;
	}
	namedWindow("src",CV_WINDOW_AUTOSIZE);
	imshow("src",src);

	Mat dst;
	//dst = Mat(src.size(),src.type());//Mat¹¹Ôìº¯Êý
	//dst = Scalar(0,0,127);
	//dst = src.clone();
	//src.copyTo(dst);

	//cvtColor(src,dst, CV_BGR2GRAY);
	//dst.create(src.size(),src.type());
	//dst = Scalar(255,0,0);
	//printf("src : %d ,dst : %d\n", src.channels(), dst.channels());

	//int row = dst.rows;
	//int col = dst.cols;
	//printf("row : %d, col : %d\n", row, col);

	//const uchar* firstRow = dst.ptr<uchar>(0);
	//printf("firstRow color : %d\n",*firstRow);
	//
	//Mat a(3, 3, CV_8UC3, Scalar(1, 1, 1));
	//cout << "a = " << endl << a << endl;
	
	//Mat hh = Mat::zeros(3, 3, CV_8UC1);
	Mat hh = Mat::eye(3, 3, CV_8UC1);
	cout << "hh : = \n" << hh << endl;



	Mat h;// (src.size(), src.type()); //= src.clone();
	Mat kernel = (Mat_<char>(3,3)  << 0,-1,0,-1,5,-1,0,-1,0);
	filter2D(src, h, src.depth(), kernel);
	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	imshow("dst", h);
	waitKey(0);
	return 0;
}