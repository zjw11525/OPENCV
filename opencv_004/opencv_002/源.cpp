#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
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

	Mat dst(src.size(),src.type());
	//cvtColor(src, dst,CV_BGR2GRAY);
	//dst = src.clone();
	int row = src.rows;
	int col = src.cols;
	int nc =  src.channels();
	for (int i = 0; i < row; i++) {
		for (int j = 0;j < col; j++) {
			if (nc == 1) {
				int Gray = src.at<uchar>(i, j);
				dst.at<uchar>(i, j) = 255 - Gray;
			}
			else if (nc == 3) {
				int Blue = src.at<Vec3b>(i, j)[0];
				int Green = src.at<Vec3b>(i, j)[1];
				int Red = src.at<Vec3b>(i, j)[2];
				//dst.at<Vec3b>(i, j)[0] = Blue;//255 - Blue;
				//dst.at<Vec3b>(i, j)[1] = Green;//255 - Green;
				//dst.at<Vec3b>(i, j)[2] = 0;//255 - Red;

				dst.at<Vec3b>(i, j)[0] = max(Red, max(Blue,Green));//子業
				dst.at<Vec3b>(i, j)[1] = max(Red, max(Blue, Green));//子業
				dst.at<Vec3b>(i, j)[2] = max(Red, max(Blue, Green));//子業
			}
		}
	}
	namedWindow("dst", CV_WINDOW_AUTOSIZE);
	imshow("dst", dst);

	//Mat a(src.size(),src.type());
	//bitwise_not(src,a);
	//namedWindow("a", CV_WINDOW_AUTOSIZE);
	//imshow("a", a);
	waitKey(0);
	return 0;
}