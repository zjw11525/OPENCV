#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() 
{
	Mat dst, src, gray ,edge_image;
	src = imread("1.jpg");
	imshow("src", src);
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, gray, CV_BGR2GRAY);
	Laplacian(gray, edge_image, CV_16S, 3);
	convertScaleAbs(edge_image, edge_image);

	threshold(edge_image, edge_image, 0, 255, THRESH_OTSU | THRESH_BINARY);
	imshow("edge_image", edge_image);
	waitKey(0);
	return 0;
}
