#include"opencv2/opencv.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include<iostream>

using namespace std;
using namespace cv;

////��׼����任
//int main()
//{
//	Mat src_img = imread("D://OpenCV_coding/test_img/social_coding_567_416.jpg");
//	Mat mid_img,dst_img;
//
//	Canny(src_img,mid_img,50,150);
//	cvtColor(mid_img,dst_img,CV_GRAY2BGR);
//
//	//imshow("the temp window",dst_img);
//
//	vector<Vec2f> lines;
//	HoughLines(mid_img,lines,1,CV_PI/180,100,0,0);
//	/*
//	��������˵����
//	����1�������ԭʼͼ��
//	����2�Ǿ��������߱任�õ���ֱ�ߵ����ʸ��(rho,theta)��
//	����3��ֱ������ʱ�Ĳ�����λ���ȣ�������Ϊ��λ��
//	����4��ֱ������ʱ�Ĳ�����λ�Ƕȣ��Ի���Ϊ��λ��
//	����5���ۼ�ƽ�����ֵ����ʶ��ĳ����Ϊͼ��һ��ֱ��ʱ�������ۼ�ƽ���б���ﵽ����ֵ��
//	����6�Ǿ�ȷ�ۼ�ʱ�ľ��ȳ�����������Ϊ��ȷ�ۼ�ʱ�ĳ��Ȳ������ȣ�
//	����7ʱ��ȷ�ۼ�ʱ�ľ��ȳ�����������Ϊ��ȷ�ۼ�ʱ�ĽǶȲ������ȡ�
//	*/
//	for(size_t i = 0;i < lines.size();i++)
//	{
//		float rho = lines[i][0],theta = lines[i][1];
//		Point pt1,pt2;
//		double a = cos(theta),b = sin(theta);
//		double x0 = a * rho,y0 = b * rho;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//		pt1.y = cvRound(y0 + 1000 * (a));
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * (a));
//
//		line(dst_img,pt1,pt2,Scalar(55,100,195),1,8,0);
//	}
//	
//	imshow("the origin image",src_img);
//	imshow("the cannny image",mid_img);
//	imshow("the result image",dst_img);
//
//	waitKey(0);
//	return 0;
//}

////�ۼƸ��ʵĻ����߱任
//int main()
//{
//	Mat src_img = imread("D://OpenCV_coding/test_img/social_coding_567_416.jpg");
//	Mat mid_img,dst_img;
//
//	Canny(src_img,mid_img,50,200,3);
//	cvtColor(mid_img,dst_img,COLOR_GRAY2BGR);
//
//	vector<Vec4i> lines;
//	HoughLinesP(mid_img,lines,1,CV_PI/180,80,50,10);
//
//	for(size_t i = 0;i < lines.size();i++)
//	{
//		Vec4i l = lines[i];
//		line(dst_img,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(186,88,255),1,CV_AA);
//	}
//
//	imshow("the origin image",src_img);
//	imshow("the canny image",mid_img);
//	imshow("the result image",dst_img);
//
//	waitKey(0); 
//	return 0;
//}

int main()
{
	Mat src_img = imread("D://OpenCV_coding/test_img/social_coding_567_416.jpg");
	Mat mid_img,dst_img;

	imshow("the origin image",src_img);

	cvtColor(src_img,mid_img,CV_BGR2GRAY,0);
	GaussianBlur(mid_img,mid_img,Size(9,9),2,2);

	vector<Vec3f> circles;
	HoughCircles(mid_img,circles,CV_HOUGH_GRADIENT,1.5,10,200,87,0,0);

	for(size_t i = 0;i < circles.size();i++)
	{
		Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circle(src_img,center,3,Scalar(0,255,0),-1,8,0);//����������ʾ������ʵ��Բ
		circle(src_img,center,radius,Scalar(123,123,123),3,8,0);
	}

	imshow("the result image",src_img);
	waitKey(0);
	return 0;
}