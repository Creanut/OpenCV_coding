#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

#define WINDOWNAME1 "the origin image"
#define WINDOWNAME2 "the result image"

Mat g_src_img,g_gray_img;
int g_thresh_val = 50;
int g_max_thresh = 255;
RNG g_rng(12345);
Mat g_src_img_copy = g_src_img.clone();
Mat g_threshold_img;
vector<vector<Point>> g_contours;
vector<Vec4i> g_hierarchy;

void on_thresh_change(int,void *);

int main()
{
	g_src_img = imread("D://OpenCV_coding/test_img/colorful_1080_678.jpg");

	cvtColor(g_src_img,g_gray_img,COLOR_BGR2GRAY);
	blur(g_gray_img,g_gray_img,Size(3,3));

	namedWindow(WINDOWNAME1,WINDOW_AUTOSIZE);
	imshow(WINDOWNAME1,g_src_img);

	createTrackbar("Val",WINDOWNAME1,&g_thresh_val,g_max_thresh,on_thresh_change);
	on_thresh_change(0,0);

	waitKey(0);
	return 0;
}

void on_thresh_change(int,void *)
{
	threshold(g_gray_img,g_threshold_img,g_thresh_val,255,THRESH_BINARY);
	findContours(g_threshold_img,g_contours,g_hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	Mat drawing = Mat::zeros(g_threshold_img.size(),CV_8UC3);

	vector<vector<Point>> hull(g_contours.size());
	for(unsigned int i = 0;i < g_contours.size();i++)
	{
		convexHull(Mat(g_contours[i]),hull[i],false);
	}

	Mat drawing = Mat::zeros(g_threshold_img.size(),CV_8UC3);
	for(unsigned int i = 0;i < g_contours.size();i++)
	{
		Scalar color = Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255));
		drawContours(drawing,hull,i,color,1,8,vector<Vec4i>(),0,Point());
	}

	imshow(WINDOWNAME2,g_threshold_img);
}
