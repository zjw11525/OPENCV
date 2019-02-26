#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src,dst;
char OUTPUT_WIN[] = "dst";
int element_size = 3;
int max_size = 21;
void CallBack_Demo(int, void*);

int main(int argc, char** argv) {

	src = imread("2.jpg", 1);

	namedWindow("dst", 1);
	imshow("dst", src);

	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);

	createTrackbar("Element Size:", OUTPUT_WIN, &element_size, max_size, CallBack_Demo);
	CallBack_Demo(0,0);

	waitKey(0);
	return 0;
}

void CallBack_Demo(int, void*)
{
	int s = element_size * 2 + 1;
	Mat structElement = getStructuringElement(MORPH_RECT,Size(s,s));
	
	//dilate(src, dst, structElement);
	erode(src,dst,structElement);
	imshow(OUTPUT_WIN, dst);
}