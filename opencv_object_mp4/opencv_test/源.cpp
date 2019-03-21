#include "opencv2/opencv.hpp"
#include <iostream>
#include <Windows.h>
using namespace std;
using namespace cv;

Mat MoveDetect(Mat frame1, Mat frame2)//��������
{
	Mat result = frame2.clone();
	Mat gray1, gray2;
	cvtColor(frame1, gray1, CV_BGR2GRAY);
	cvtColor(frame2, gray2, CV_BGR2GRAY);
	 
	Mat diff;
	absdiff(gray1, gray2, diff);
	imshow("absdiss", diff);
	threshold(diff, diff, 45, 255, CV_THRESH_BINARY);
	imshow("threshold", diff);

	//��ʴ�����˲�
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(10, 10));
	erode(diff, diff, element);
	imshow("erode", diff);
	dilate(diff, diff, element2);
	imshow("dilate", diff);

	//��ֵ����ʹ����ֵ�˲�+����
	//Mat element = getStructuringElement(MORPH_RECT, Size(11, 11));
	//medianBlur(diff, diff, 5);//��ֵ�˲�
	//imshow("medianBlur", diff);
	//dilate(diff, diff, element);
	//imshow("dilate", diff);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	//����Բ������
	findContours(diff, contours, hierarcy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE); //��������
	cout << "num = " << contours.size() << endl;
	vector<RotatedRect> box(contours.size()); //������Բ����

	for (int i = 0; i < contours.size(); i++)
	{
		box[i] = fitEllipse(Mat(contours[i]));
		ellipse(result, box[i], Scalar(0, 255, 0), 2, 8);
		circle(result, box[i].center, 3, Scalar(0,0,255),-1,8);
	}
	return result;
}

void main()
{
	VideoCapture cap(0);
	if (!cap.isOpened()) //�����Ƿ�ɹ�
		return;
	Sleep(5);
	Size size0 = Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	VideoWriter writer("C:\\Users\\Administrator\\Desktop\\out.mp4", -1, cap.get(CV_CAP_PROP_FPS), size0, false);
	Mat frame;
	Mat background;
	Mat result;
	Mat temp;
	int count = 0;
	while (1)
	{
		cap >> frame;
		if (!frame.empty())
		{
			count++;
			//��������
			if (count == 1)
				background = frame.clone(); //��ȡ��һ֡Ϊ����֡
			//imshow("video", frame);
			result = MoveDetect(background, frame);
			imshow("dst", result);
			//writer << result;
			//֡�
			//if (count == 1)
			//	result = MoveDetect(frame, frame);
			//else
			//	result = MoveDetect(temp, frame);
			////imshow("video", frame);
			//imshow("result", result);
			//temp = frame.clone();
			writer << result;
			if (waitKey(50) == 27)
				break;
		}
		else
			break;
	}
	cap.release();
	waitKey(0);
}