#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

Mat g_src_img,g_box_filtered_img,g_linear_filtered_img,g_guassian_filtered_img;
Mat g_middle_filtered_img,g_bilateral_filtered_img;
int g_box_filtered_val = 3;
int g_linear_filtered_val = 3;
int g_guassian_filtered_val = 3;
int g_middle_filtered_val = 10;
int g_bilateral_filtered_val = 10;

static void on_box_filter(int,void *);
static void on_linear_filter(int,void *);
static void on_guassian_filter(int,void *);
static void on_middle_filter(int,void *);
static void on_bilateral_filter(int,void *);

int main()
{
	//system("color5E");

	g_src_img = imread("D://OpenCV_coding/test_img/colorful_467_318.jpg");
	if(!g_src_img.data)
	{
		printf("the src_img is error!");
		return false;
	}

	g_box_filtered_img = g_src_img.clone();
	g_linear_filtered_img = g_src_img.clone();
	g_guassian_filtered_img = g_src_img.clone();
	g_middle_filtered_img = g_src_img.clone();
	g_bilateral_filtered_img = g_src_img.clone();

	namedWindow("the origin image",1);
	namedWindow("the box_filtered image",1);
	namedWindow("the linear_filtered image",1);
	namedWindow("the guassian_filtered image",1);
	namedWindow("the middle_filtered image",1);
	namedWindow("the bilateral_filtered image",1);
	imshow("the origin image",g_src_img);

	createTrackbar("the kernel val:","the box_filtered image",&g_box_filtered_val,40,on_box_filter);
	on_box_filter(g_box_filtered_val,0);

	createTrackbar("the kernel val:","the linear_filtered image",&g_linear_filtered_val,40,on_linear_filter);
	on_linear_filter(g_linear_filtered_val,0);

	createTrackbar("the kernel val:","the guassian_filtered image",&g_guassian_filtered_val,40,on_guassian_filter);
	on_guassian_filter(g_guassian_filtered_val,0);

	createTrackbar("the kernel val:","the middle_filtered image",&g_middle_filtered_val,40,on_middle_filter);
	on_middle_filter(g_middle_filtered_val,0);

	createTrackbar("the kernel val:","the bilateral_filtered image",&g_bilateral_filtered_val,40,on_bilateral_filter);
	on_bilateral_filter(g_bilateral_filtered_val,0);

	while(char(waitKey(1)) != 'q');
	return 0;
}

static void on_box_filter(int,void *)
{
	boxFilter(g_src_img,g_box_filtered_img,-1,Size(g_box_filtered_val + 1,g_box_filtered_val + 1));
	imshow("the box_filtered image",g_box_filtered_img);
}

static void on_linear_filter(int,void *)
{
	blur(g_src_img,g_linear_filtered_img,Size(g_linear_filtered_val + 1,g_linear_filtered_val + 1),Point(-1,-1));
	imshow("the linear_filtered image",g_linear_filtered_img);
}

static void on_guassian_filter(int,void *)
{
	GaussianBlur(g_src_img,g_guassian_filtered_img,Size(g_guassian_filtered_val * 2 + 1,g_guassian_filtered_val * 2 + 1),0,0);
	imshow("the guassian_filtered image",g_guassian_filtered_img);
}

static void on_middle_filter(int,void *)
{
	medianBlur(g_src_img,g_middle_filtered_img,g_middle_filtered_val * 2 + 1);
	imshow("the middle_filtered image",g_middle_filtered_img);
}

static void on_bilateral_filter(int,void *)
{
	bilateralFilter(g_src_img,g_bilateral_filtered_img,g_bilateral_filtered_val,g_bilateral_filtered_val * 2,g_bilateral_filtered_val / 2);
	imshow("the bilateral_filtered image",g_bilateral_filtered_img);
}
