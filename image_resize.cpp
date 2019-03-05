#include"opencv2/opencv.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main()
{
	Mat src_img = imread("D://OpenCV_coding/test_img/colorful_467_318.jpg");
	Mat tmp_img,dst_img1,dst_img2;
	tmp_img = src_img;

	imshow("the origin image",src_img);

	resize(tmp_img,dst_img1,Size(tmp_img.cols / 2,tmp_img.rows / 2),(0,0),(0,0),INTER_LINEAR);
	resize(tmp_img,dst_img2,Size(tmp_img.cols * 2,tmp_img.rows * 2),(0,0),(0,0),INTER_LINEAR);

	imshow("the result image 1",dst_img1);
	imshow("teh result image 2",dst_img2);

	waitKey(0);
	return 0;
}