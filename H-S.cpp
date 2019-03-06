#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src_img,hsv_img;
	src_img = imread("D://OpenCV_coding/test_img/colorful_467_318.jpg");
	cvtColor(src_img,hsv_img,COLOR_BGR2HSV);

	int hue_bin_num = 30;
	int saturation_bin_num = 32;
	int hist_size[] = {hue_bin_num,saturation_bin_num};

	float hue_ranges[] = {0,180};
	float saturation_ranges[] = {0,256};
	const float* ranges[] = {hue_ranges,saturation_ranges};
	MatND dst_hist;

	int channels[] = {0,1};

	calcHist(&hsv_img,
		1,
		channels,
		Mat(),
		dst_hist,
		2,
		hist_size,
		ranges,
		true,
		false
		);

	double max_val = 0;
	minMaxLoc(dst_hist,0,&max_val,0,0);
	int scale = 10;
	Mat hist_img = Mat::zeros(saturation_bin_num*scale,hue_bin_num*10,CV_8UC3);

	for(int hue = 0;hue < hue_bin_num;hue++)
		for(int saturation = 0;saturation < saturation_bin_num;saturation++)
		{
			float bin_val = dst_hist.at<float>(hue,saturation);
			int intensity = cvRound(bin_val * 255 / max_val);

			rectangle(hist_img,
				Point(hue * scale,saturation * scale),
				Point((hue + 1) * scale - 1,(saturation + 1) * scale - 1),
				Scalar::all(intensity),
				100,
				8,
				0);
		}

		imshow("the origin image",src_img);
		imshow("the H-S hist",hist_img);

		waitKey();
}