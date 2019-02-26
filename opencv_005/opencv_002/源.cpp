#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src,src1,dst;
	src = imread("1.jpg");
	if (src.empty()) {
		cout << "could not load the image..." << endl;
		return -1;
	}
	namedWindow("src",CV_WINDOW_AUTOSIZE);
	imshow("src",src);

	src1 = imread("2.jpg");
	if (src1.empty()) {
		cout << "could not load the image..." << endl;
		return -1;
	}
	namedWindow("src1", CV_WINDOW_AUTOSIZE);
	imshow("src1", src1);

	double alpha = 0.2;
	if (src.rows == src1.rows && src.cols == src1.cols && src.type() == src1.type()){
		//addWeighted(src,alpha,src1,1 - alpha,0.0,dst);
		//add(src,src1,dst,Mat());
		multiply(src, src1, dst, 1.0);
		imshow("dst",dst);
	}

	waitKey(0);
	return 0;
}