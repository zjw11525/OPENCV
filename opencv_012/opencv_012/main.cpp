#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
	Mat src(600,600,CV_8UC3,Scalar(0,255,0));
	imshow("stc",src);
	waitKey(0);
	return 0;
}