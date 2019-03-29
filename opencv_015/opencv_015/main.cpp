#include <iostream>
#include "opencv2/opencv.hpp"
#include <Windows.h>

using namespace std;
using namespace cv;

int main() 
{
	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;
	Sleep(5);
	Mat frame,dst;

	cap >> frame;

	int index = 0;
	int ksize = 0;
	while (true) 
	{

		ksize = 4 + (index % 5) * 2 + 1;
		Mat kernel = Mat::ones(Size(ksize, ksize), CV_32F) / (float)(ksize*ksize);
		filter2D(frame, dst, -1, kernel, Point(-1, -1));
		index++;
		imshow("cap", dst);

		////Robert X方向
		//Mat kernel_x = (Mat_<int>(2, 2) << 1, 0, 0, -1);
		//filter2D(frame, dst, -1, kernel_x, Point(-1, -1), 0.0);
		//imshow("dst", dst);

		////Robert Y方向
		//Mat kernel_y = (Mat_<int>(2, 2) << 0, 1, -1, 0);
		//filter2D(frame, dst, -1, kernel_y, Point(-1, -1), 0.0);
		//imshow("dst1", dst);

		////Sobel算子  x方向
		//Mat kernel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
		//filter2D(frame, dst, -1, kernel_x, Point(-1, -1), 0.0);
		//imshow("dst", dst);

		////Sobel算子  y方向
		//Mat kernel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
		//filter2D(frame, dst, -1, kernel_y, Point(-1, -1), 0.0);
		//imshow("dst1", dst);

		//拉普拉斯算子
		//Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
		//filter2D(frame, dst, -1, kernel, Point(-1, -1), 0.0);
		//imshow("dst", dst);
		

		if (cv::waitKey(500) == 27)
			break;//50MS刷新图像，按ESC退出
	}
	cv::waitKey(0);//0 一直等待
	return 0;
}