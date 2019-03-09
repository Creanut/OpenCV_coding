#include"opencv2/opencv.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include<iostream>

using namespace std;
using namespace cv;

////标准霍夫变换
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
//	函数参数说明：
//	参数1是输入的原始图像；
//	参数2是经过霍夫线变换得到的直线的输出矢量(rho,theta)；
//	参数3是直线搜索时的步进单位长度，以像素为单位；
//	参数4是直线搜索时的步进单位角度，以弧度为单位；
//	参数5是累加平面的阈值，即识别某部分为图中一条直线时，它在累加平面中必须达到的阈值；
//	参数6是精确累加时的精度除数，计算结果为精确累加时的长度步进精度；
//	参数7时精确累加时的精度除数，计算结果为精确累加时的角度步进精度。
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

////累计概率的霍夫线变换
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

		circle(src_img,center,3,Scalar(0,255,0),-1,8,0);//负数参数表示画的是实心圆
		circle(src_img,center,radius,Scalar(123,123,123),3,8,0);
	}

	imshow("the result image",src_img);
	waitKey(0);
	return 0;
}