#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src_img = imread("D://OpenCV_coding/test_img/colorful_467_318.jpg");
	Mat src_img1 = src_img.clone();

	imshow("the origin image",src_img);

	Canny(src_img,src_img,100,150,3);
	imshow("the result image_1",src_img);

	Mat dst_img,edge_img,gray_img;
	dst_img.create(src_img1.size(),src_img1.type());

	cvtColor(src_img1,gray_img,COLOR_BGR2GRAY);
	blur(gray_img,edge_img,Size(3,3));
	Canny(edge_img,edge_img,3,9,3);
	dst_img = Scalar::all(0);
	src_img1.copyTo(dst_img,edge_img);
	imshow("the result image",dst_img);

	waitKey(0);
	return 0;
}