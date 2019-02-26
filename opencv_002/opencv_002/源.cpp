#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("1.jpg");
	if (!src.data) {
		printf("could not read the image\n");
		return -1;
	}
	namedWindow("src",CV_WINDOW_AUTOSIZE);
	imshow("src",src);
	
	double t = getTickCount();
/*	int cols = (src.cols - 1)*src.channels();
	int offsetX = src.channels();
	int rows = src.rows;
	dst = Mat::zeros(src.size(),src.type());
	for (int row = 1; row < (rows - 1); row++) {
		const uchar* previous = src.ptr<uchar>(row - 1);
		const uchar* current = src.ptr<uchar>(row);
		const uchar* next = src.ptr<uchar>(row + 1);
		uchar* output = dst.ptr<uchar>(row);
		for (int col = offsetX; col < cols; col++) {
			output[col] = saturate_cast<uchar>( 5 * current[col] - (current[col - offsetX] + current[col + offsetX] + previous[col] + next[col]));
		}
	}*///0.037348

	Mat kernel = (Mat_<char>(3, 3) << 0,-1,0,-1,5,-1,0,-1,0);
	filter2D(src,dst,src.depth(),kernel);
	double timeconsume = (getTickCount() - t) / getTickFrequency();//0.147008
	printf("time consume %f\n",timeconsume);

	namedWindow("dst",CV_WINDOW_AUTOSIZE);
	imshow("dst",dst);
	waitKey(0);
	return 0;
}