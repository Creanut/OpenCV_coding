#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "³ÌÐò´°¿Ú"

int g_threshold_val = 100;
int g_threshold_type = 3;
Mat g_src_img,g_dst_img,g_gray_img;

void on_threshold(int,void *);

int main()
{
	g_src_img = imread("D://OpenCV_coding/test_img/colorful_1080_678.jpg");
	if(!g_src_img.data)
	{
		printf("the src_img is error!");
		return false;
	}

	cvtColor(g_src_img,g_gray_img,COLOR_RGB2GRAY);
	namedWindow(WINDOW_NAME,WINDOW_AUTOSIZE);
	createTrackbar("MODE",WINDOW_NAME,&g_threshold_type,4,on_threshold);
	createTrackbar("VALUE",WINDOW_NAME,&g_threshold_val,255,on_threshold);

	on_threshold(0,0);

	while(1)
	{
		int key;
		key = waitKey(20);
		if((char)key == 27)
			break;
	}
}

void on_threshold(int,void *)
{
	threshold(g_gray_img,g_dst_img,g_threshold_val,255,g_threshold_type);
	imshow(WINDOW_NAME,g_dst_img);
}