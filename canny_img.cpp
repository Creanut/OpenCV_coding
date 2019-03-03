#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat src_img = imread("D://OpenCV_coding/test_img/social_coding.jpg");
	imshow("the original image",src_img);

	Mat edge_img,gray_img;

	cvtColor(src_img,gray_img,CV_BGR2BGRA);
	imshow("the gray image",gray_img);

	blur(gray_img,edge_img,Size(3,3));
	Canny(edge_img,edge_img,3,9,3);

	imshow("the canny image",edge_img);

	waitKey(0);
	return 0;
}