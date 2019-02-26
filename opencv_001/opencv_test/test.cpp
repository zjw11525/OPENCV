#include<iostream>


#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>


using namespace cv;


int main()


{


	Mat picture = imread("1_143855_3.jpg");//图片必须添加到工程目录下
	if (picture.empty()) {
		printf("could not read the picture\n");
		return -1;
	}
	namedWindow("source picture",CV_WINDOW_AUTOSIZE);
	imshow("source picture", picture);

	Mat output;
	cvtColor(picture,output,CV_BGR2HLS);

	namedWindow("gray picture", CV_WINDOW_AUTOSIZE);
	imshow("gray picture", output);

	//imshow("测试程序", picture);
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//Mat dstimage;
	//erode(picture, dstimage, element);
	//imshow("腐蚀操作", dstimage);




	waitKey(0);


}