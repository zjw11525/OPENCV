// opencv_014.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include <Windows.h>

using namespace std;
using namespace cv;

Mat frame;
Mat gray;
Mat dst;
int threshold_value = 127;
int threshold_max = 255;
int type = 2;
int type_max = 4;
void threshold_demo(int, void*);

int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;
	Sleep(5);
	while (1) 
	{
		cap >> frame;
		if (!frame.empty()) 
		{
			imshow("video", frame);
			
			createTrackbar("Threshold Value", "dst", &threshold_value, threshold_max, threshold_demo);
			createTrackbar("Threshold Typr", "dst", &type, type_max, threshold_demo);
			threshold_demo(0, 0);
			
			if (waitKey(50) == 27)
				break;
		}
	}
    std::cout << "Hello World!\n"; 
	cap.release();
	waitKey(0);
	return 0;
}

void threshold_demo(int, void*) 
{
	cvtColor(frame, gray, CV_BGR2GRAY);
	threshold(gray, dst, threshold_value, threshold_max, THRESH_TRIANGLE | type);
	imshow("dst", dst);
}