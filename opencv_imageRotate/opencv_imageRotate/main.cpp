#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void RotateImageCorrect(Mat srcImg) 
{
	Mat dst,gray, binImg;
	cvtColor(srcImg, gray, CV_BGR2GRAY, 0);
	imshow("gray",gray);
	threshold(gray, binImg, 100, 200, CV_THRESH_BINARY);
	imshow("binary", binImg);

	vector<vector<Point> > contours;
	vector<Rect> boundRect(contours.size());
	//ע���5������ΪCV_RETR_EXTERNAL��ֻ�������  
	findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //������
	cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++)
	{
		//��Ҫ��ȡ������  
		CvPoint2D32f rectpoint[4];
		CvBox2D rect = minAreaRect(Mat(contours[i]));

		cvBoxPoints(rect, rectpoint); //��ȡ4����������  
		//��ˮƽ�ߵĽǶ�  
		float angle = rect.angle;
		cout << angle << endl;

		int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
		int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
		//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
		//���̫С��ֱ��pass
		if (line1 * line2 < 600)
		{
			continue;
		}

		//Ϊ���������κ��ŷţ�������ת�Ƕ��ǲ�һ���ġ����ŵģ�������90�ȣ�������  
		if (line1 > line2)
		{
			angle = 90 + angle;
		}

		//�½�һ������Ȥ������ͼ����С��ԭͼһ����  
		Mat RoiSrcImg(srcImg.rows, srcImg.cols, CV_8UC3); //ע���������ѡCV_8UC3
		RoiSrcImg.setTo(0); //��ɫ������Ϊ��ɫ  
		//imshow("�½���ROI", RoiSrcImg);
		//�Եõ����������һ��  
		drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);

		//��ͼ��RoiSrcImg
		srcImg.copyTo(RoiSrcImg, binImg);


		//����ʾһ�¿��������˸���Ȥ�������������ֶ��Ǻ�ɫ����  
		namedWindow("RoiSrcImg", 1);
		imshow("RoiSrcImg", RoiSrcImg);

		//����һ����ת���ͼ��  
		Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
		RatationedImg.setTo(0);
		//��RoiSrcImg������ת  
		Point2f center = rect.center;  //���ĵ�  
		Mat M2 = getRotationMatrix2D(center, angle, 1);//������ת�����ŵı任���� 
		warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//����任 
		imshow("��ת֮��", RatationedImg);
		imwrite("r.jpg", RatationedImg); //���������ͼƬ��������
	}
}

int main() 
{
	Mat src = imread("1.jpg");
	imshow("src",src);
	RotateImageCorrect(src);
	waitKey(0);
	return 0;
}