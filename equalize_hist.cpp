#include"opencv2/opencv.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src_img,dst_img;
	src_img = imread("D://OpenCV_coding/test_img/timg (2).jpg");
	if(!src_img.data)
	{
		printf("the src_img is error!");
		return false;
	}

	cvtColor(src_img,src_img,CV_BGR2GRAY);
	imshow("the origin image",src_img);

	equalizeHist(src_img,dst_img); 
	imshow("the equalized image",dst_img);

	waitKey(0);
	return 0;
}