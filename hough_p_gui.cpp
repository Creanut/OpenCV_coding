#include"opencv2/opencv.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

Mat g_src_img,g_dst_img,g_mid_img;
vector<Vec4i> g_lines;
int g_threshold = 100;

static void on_houghlines(int,void *);

int main()
{
	Mat g_src_img = imread("D://OpenCV_coding/test_img/colorful_1080_678.jpg");
	imshow("the origin image",g_src_img);

	namedWindow("the result image",1);
	createTrackbar("Val","the result image",&g_threshold,200,on_houghlines);
		
	Canny(g_src_img,g_mid_img,50,200,3);
	//cvtColor(g_mid_img,g_mid_img,CV_GRAY2BGR);
	//imshow("the middle image",g_mid_img);
	
	HoughLinesP(g_mid_img,g_lines,1,CV_PI/180,80,50,10);
	on_houghlines(g_threshold,0);
	//
	//imshow("the result image",g_dst_img);

	waitKey(0);
	return 0;
}

static void on_houghlines(int,void *)
{
	Mat dst_img = g_dst_img.clone();
	Mat mid_img = g_mid_img.clone();

	vector<Vec4i> my_lines;
	HoughLinesP(mid_img,my_lines,1,CV_PI/180,g_threshold+1,50,10);

	for(size_t i = 0;i < my_lines.size();i++)
	{
		Vec4i l = my_lines[i];
		line(dst_img,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(123,23,3),1,8);
		
		//imshow("the result image",dst_img);
	}
}
