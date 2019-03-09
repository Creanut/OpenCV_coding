#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

//sobel算子应用
//int main()
//{
//	Mat grad_x,grad_y;
//	Mat abs_grad_x,abs_grad_y,dst_img;
//	Mat src_img = imread("D://OpenCV_coding/test_img/social_coding_567_416.jpg");
//
//	imshow("the origin image",src_img);
//
//	Sobel(src_img,grad_x,CV_16S,1,0,3,1,1,BORDER_DEFAULT);
//	convertScaleAbs(grad_x,abs_grad_x);
//	imshow("the sobel in X",abs_grad_x);
//
//	Sobel(src_img,grad_y,CV_16S,0,1,3,1,1,BORDER_DEFAULT);
//	convertScaleAbs(grad_y,abs_grad_y);
//	imshow("the sobel in Y",abs_grad_y);
//
//	addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst_img);
//	imshow("the result image",dst_img);
//
//	waitKey(0);
//	return 0;
//}

//laplace算子应用
//int main()
//{
//	Mat src_img,src_gray,dst_img,abs_dst_img;
//
//	src_img = imread("D://OpenCV_coding/test_img/social_coding_567_416.jpg");
//	imshow("the origin image",src_img);
//
//	GaussianBlur(src_img,src_img,Size(3,3),0,0,BORDER_DEFAULT);
//	cvtColor(src_img,src_gray,COLOR_BGR2GRAY);
//	Laplacian(src_gray,dst_img,CV_16S,3,1,0,BORDER_DEFAULT);
//	convertScaleAbs(dst_img,abs_dst_img);
//	imshow("the result image",abs_dst_img);
//
//	waitKey(0);
//	return 0;
//}

//scharr滤波器应用
int main()
{
	Mat grad_x,grad_y;
	Mat abs_grad_x,abs_grad_y;
	Mat dst_img;
	Mat src_img = imread("D://OpenCV_coding/test_img/social_coding_567_416.jpg");
	imshow("the origin image",src_img);

	Scharr(src_img,grad_x,CV_16S,1,0,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_x,abs_grad_x);
	imshow("scharr in X",abs_grad_x);

	Scharr(src_img,grad_y,CV_16S,0,1,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_y,abs_grad_y);
	imshow("scharr in Y",abs_grad_y);

	addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst_img);

	imshow("the result image",dst_img);

	waitKey(0);
	return 0;
}