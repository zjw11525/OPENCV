#include <iostream>
#include "opencv2/opencv.hpp"
#include <Windows.h>
using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}
	
	Sleep(5);
	
	Mat frame,dst;
	RNG rng;
	cap >> frame;
	int top = (int)(0.05*frame.rows);
	int bottom = (int)(0.05*frame.rows);
	int left = (int)(0.05*frame.cols);
	int right = (int)(0.05*frame.cols);
	int bordertype = BORDER_DEFAULT;
	while (1) 
	{
		cap >> frame;
		imshow("video", frame);
		char c = waitKey(10);
		switch (c) 
		{
			case 27: return 0; break;
			case 'q': bordertype = BORDER_REPLICATE; break;
			case 'w': bordertype = BORDER_WRAP; break;
			case 'e': bordertype = BORDER_CONSTANT; break;
			case 'r': bordertype = BORDER_DEFAULT; break;
		}
		//Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//copyMakeBorder(frame,dst,top,bottom,left,right,bordertype,color);
		GaussianBlur(frame, dst, Size(5, 5), 0, 0, bordertype);
		imshow("dst",dst);
	}
	waitKey(0);
	return 0;
}