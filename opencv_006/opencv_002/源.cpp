#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src1 = imread("2.jpg");
	if (!src1.data) {
		return -1;
	}
	imshow("src",src1);
	Mat gray(src1.size(),src1.type());

	/*cvtColor(src1, gray, CV_BGR2GRAY);
	imshow("gray",gray);*/
	Mat src;
	src = src1.clone();
	//src1.convertTo(src,CV_32F);

	cvtColor(src, src, CV_BGR2GRAY);
	imshow("src",src);
	Mat dst(src.size(),src.type());
	int rows = src1.rows;
	int cols = src1.cols;
	int alpha = 1.5;
	int beta = 20;
	
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (src.channels() == 3) {
				float b = src.at<Vec3f>(row, col)[0];
				float g = src.at<Vec3f>(row, col)[1];
				float r = src.at<Vec3f>(row, col)[2];
				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha * b + beta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha * g + beta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha * r + beta);
			}
			else if (src.channels() == 1) {
				float gg = src.at<uchar>(row, col);
				dst.at<uchar>(row,col) = saturate_cast<uchar>(1.2 * gg + 30);
			}
			
		}
	}

	imshow("dst",dst);

	waitKey(0);
	return 0;
}