#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace std;
using namespace cv;

Mat g_src_img,g_dst_img,g_gray_img,g_mask_img;
int g_floodfill_mode = 1;
int g_low_difference = 20;
int g_up_difference = 20;
int g_low8_connectivity = 4;
int g_bool_is_color = true;
int g_bool_is_mask = false;
int g_new_mask_val = 255;

static void on_mouse(int event,int x,int y,int,void *)
{
	if(event != CV_EVENT_LBUTTONDOWN)
		return;

	Point seed = Point(x,y);
	int low_difference = g_floodfill_mode == 0 ? 0 : g_low_difference;
	int up_difference = g_floodfill_mode == 0 ? 0 : g_up_difference;
	int flags = g_low8_connectivity + (g_new_mask_val << 8) + (g_floodfill_mode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	int b = (unsigned)theRNG() & 255;
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;

	Scalar new_val = g_bool_is_color ? Scalar(b,g,r) : Scalar(r * 0.299 + g * 0.587 + b * 0.114);
	Mat dst_img = g_bool_is_color ? g_dst_img : g_gray_img;
	int area;

	if(g_bool_is_mask)
	{
		threshold(g_mask_img,g_mask_img,1,128,CV_THRESH_BINARY);
		area = floodFill(dst_img,g_mask_img,seed,new_val,&ccomp,Scalar(low_difference,low_difference,low_difference),
			Scalar(up_difference,up_difference,up_difference),flags);
		imshow("mask image",g_mask_img);
	}
	else
	{
		area = floodFill(dst_img,seed,new_val,&ccomp,Scalar(low_difference,low_difference,low_difference),
			Scalar(up_difference,up_difference,up_difference),flags);
	}

	imshow("the result image",dst_img);
	cout << "there are " << area << " recolored\n";
}

int main()
{
	g_src_img = imread("D://OpenCV_coding/test_img/social_coding_567_416.jpg");
	if(!g_src_img.data)
	{
		printf("the src_img is error!");
		return false;
	}
	imshow("the origin image",g_src_img);

	g_dst_img = g_src_img.clone();
	cvtColor(g_src_img,g_gray_img,COLOR_BGR2GRAY);
	g_mask_img.create(g_src_img.rows + 2,g_src_img.cols + 2,CV_8UC1);

	namedWindow("the result image",CV_WINDOW_AUTOSIZE);

	createTrackbar("MAX LOWDIFFERENCE","the result image",&g_low_difference,255,0);
	createTrackbar("MAX UPDIFFERENCE","the result image",&g_up_difference,255,0);
	setMouseCallback("the result image",on_mouse,0);

	while(1)
	{
		imshow("the result image",g_bool_is_color ? g_dst_img : g_gray_img);

		int c;
		c = waitKey(0);
		if(c & 255 == 27)
		{
			printf("the program is escaping ...");
			break;
		}

		switch((char)c)
		{
		case '1':
			if(g_bool_is_color)
			{
				cout << "the '1' is down, the function is converting the image mode! the mode will shift to GRAY...\n";
				cvtColor(g_src_img,g_gray_img,COLOR_BGR2GRAY);
				g_mask_img = Scalar::all(0);
				g_bool_is_color = false;
			}
			else
			{
				cout << "the '1' is down, the function is converting the image mode! the mode will shift to RGB...\n";
				g_dst_img = g_src_img.clone();
				g_mask_img = Scalar::all(0);
				g_bool_is_color = true;
			}
			break;

		case '2':
			if(g_bool_is_mask)
			{
				cout << "the '2' is down, the function is control the mask image window! the mask window will be HIDDEN...\n";
				destroyWindow("mask image");
				g_bool_is_mask = false;
			}
			else
			{
				namedWindow("mask image",0);
				g_mask_img = Scalar::all(0);
				imshow("mask image",g_mask_img);
				g_bool_is_mask = true;
			}
			break;

		case '3':
			cout << "the '3' is down, the function is recoverying the original image! the image will be RECOVERIED...\n";
			g_dst_img = g_src_img.clone();
			cvtColor(g_dst_img,g_gray_img,COLOR_BGR2GRAY);
			g_mask_img = Scalar::all(0);
			break;

		case '4':
			cout << "the '4' is down, the function is floodfilling with empty range! the mode will change to EMPTY RANGE...\n";
			g_floodfill_mode = 0;
			break;

		case '5':
			cout << "the '5' is down, the function is floodfilling with gradually change & static range! the mode will change to GRADUALLY CHANGE & STATIC RANGE...\n";
			g_floodfill_mode = 1;
			break;

		case '6':
			cout << "the '6' is down, the function is floodfilling with gradually change & floating range! the mode will change to GRADUALLY CHANGE & FLOATING RANGE...\n";
			g_floodfill_mode = 2;
			break;

		case '7':
			cout << "the '7' is down, the function is make the g_low8_connectivity to be 4! the g_low8_connectivity will be 4...\n";
			g_low8_connectivity = 4;
			break;

		case '8':
			cout << "the '8' is down, the function is make the g_low8_connectivity to be 8! the g_low8_connectivity will be 8...\n";
			g_low8_connectivity = 8;
			break;
		}
	}
	return 0;
}
