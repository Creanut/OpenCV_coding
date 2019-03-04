#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace std;
using namespace cv;

Mat g_src_img,g_gray_img,g_dst_img;
Mat g_canny_img;

int g_canny_low_threshold = 1;

Mat g_sobel_grad_x,g_sobel_grad_y;
Mat g_sobel_abs_grad_x,g_sobel_abs_grad_y;
int g_sobel_kernel_size = 1;

Mat g_scharr_grad_x,g_scharr_grad_y;
Mat g_scharr_abs_grad_x,g_scharr_abs_grad_y;

static void on_canny(int,void *);
static void on_sobel(int,void *);
void scharr();

int main()
{
	g_src_img = imread("D://OpenCV_coding/test_img/colorful_1080_678.jpg");
	if(!g_src_img.data)
	{
		printf("the src_img is error!");
		return 0;
	}

	namedWindow("the origin image");
	imshow("the origin image",g_src_img);
	g_dst_img.create(g_src_img.size(),g_src_img.type());

	cvtColor(g_src_img,g_gray_img,COLOR_BGR2GRAY);

	namedWindow("the canny edge image",WINDOW_AUTOSIZE);
	namedWindow("the sobel edge image",WINDOW_AUTOSIZE);
	namedWindow("the scharr edge image",WINDOW_AUTOSIZE);

	createTrackbar("the val","the canny edge image",&g_canny_low_threshold,120,on_canny,0);
	createTrackbar("the val","the sobel edge image",&g_sobel_kernel_size,3,on_sobel);

	on_canny(0,0);
	on_sobel(0,0);
	scharr();

	while(char(waitKey(1)) != 'q');
	return 0;
}

static void on_canny(int,void *)
{
	blur(g_gray_img,g_canny_img,Size(3,3));
	Canny(g_canny_img,g_canny_img,g_canny_low_threshold,g_canny_low_threshold * 3,3,false);

	g_dst_img = Scalar::all(0);
	g_src_img.copyTo(g_dst_img,g_canny_img);

	imshow("the canny edge image",g_dst_img);
}

static void on_sobel(int,void *)
{
	Sobel(g_src_img,g_sobel_grad_x,CV_16S,1,0,(g_sobel_kernel_size * 2 + 1),1,1,4);
	convertScaleAbs(g_sobel_grad_x,g_sobel_abs_grad_x);

	Sobel(g_src_img,g_sobel_grad_y,CV_16S,0,1,(g_sobel_kernel_size * 2 + 1),1,1,4);
	convertScaleAbs(g_sobel_grad_y,g_sobel_abs_grad_y);

	addWeighted(g_sobel_abs_grad_x,0.5,g_sobel_abs_grad_y,0.5,0,g_dst_img);

	imshow("the sobel edge image",g_dst_img);
}

void scharr()
{
	Scharr(g_src_img,g_scharr_grad_x,CV_16S,1,0,1,0,4);
	convertScaleAbs(g_scharr_grad_x,g_scharr_abs_grad_x);

	Scharr(g_src_img,g_scharr_grad_y,CV_16S,0,1,1,0,4);
	convertScaleAbs(g_scharr_grad_y,g_scharr_abs_grad_y);

	addWeighted(g_scharr_abs_grad_x,0.5,g_scharr_abs_grad_y,0.5,0,g_dst_img);

	imshow("the scharr edge image",g_dst_img);
}
