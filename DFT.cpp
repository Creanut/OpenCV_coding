#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat src_img = imread("D://OpenCV_coding/test_img/colorful_467_318.jpg",0);
	if(!src_img.data)
	{
		printf("the src_img is error!");
		return false;
	}
	imshow("the origin image",src_img);
	//cout << "the origin image matrix is" << src_img << endl;

	int m = getOptimalDFTSize(src_img.rows);
	int n = getOptimalDFTSize(src_img.cols);

	//printf("%d,%d",m-src_img.rows,n-src_img.cols);

	Mat padded;
	padded.create(src_img.rows,src_img.cols,src_img.type());
	//cout << "the padded matrix is" << padded << endl;

	//padded.type = src_img.type;
	//printf("%d",padded.type());
	copyMakeBorder(src_img,padded,0,m - src_img.rows,0,n - src_img.cols,BORDER_CONSTANT,Scalar::all(0));
	printf("%d,%d",padded.rows,padded.cols);

	//Mat planes_1 = Mat_<float>(padded);
	//为傅里叶变换结果分配存储空间
	/*傅里叶变换的结果为复数，即每一个像素点的变换结果都会有实数部分和虚数部分，即结果会有两个图像值
	 并且频域值范围远远超过空间值范围，因此需要将频域值存储在float格式中，即需要将原图像值转换为float类型，
	 以作为频域值的存储空间，并且需要额外增加一个通道以存储复数*/
	Mat planes_1 ;
	padded.convertTo(planes_1,CV_32F);
	Mat planes_2 = Mat::zeros(padded.size(),CV_32F);
	Mat planes[] = {planes_1,planes_2};
	Mat complex_i;
	merge(planes,2,complex_i);


	dft(complex_i,complex_i);

	split(complex_i,planes);//将实部和虚部分开
	magnitude(planes[0],planes[1],planes[0]);//计算幅值，并将幅值计算结果存储在planes[0]内
	Mat magnitude_img = planes[0];//得到幅值矩阵
	//imshow("the magnitude image",magnitude_img);

	//进行对数尺度的缩放，计算公式：M=log(1+M)
	magnitude_img += Scalar::all(1);
	log(magnitude_img,magnitude_img);
	//imshow("the magnitude image",magnitude_img);
	//将数值与-2进行&运算，得到的结果是找到不大于这个数的最大的偶数值，此处运算就是若有奇数行或者奇数列，则对频谱进行剪裁
	magnitude_img = magnitude_img(Rect(0,0,magnitude_img.cols & -2,magnitude_img.rows & -2));
	//normalize(magnitude_img,magnitude_img,0,1,CV_MINMAX);
	//imshow("the middle image",magnitude_img);

	//int test_m = 77;
	//int test_n = 90;

	//printf("%d,%d",(test_m & -2),(test_n & -2));

	int cx = magnitude_img.cols/2;
	int cy = magnitude_img.rows/2;
	Mat q0(magnitude_img,Rect(0,0,cx,cy));//原图的左上象限（左上坐标0,0；右下坐标cx,cy）
	Mat q1(magnitude_img,Rect(cx,0,cx,cy));//原图的右上象限（左上坐标cx,0;右下坐标cx,cy）
	Mat q2(magnitude_img,Rect(0,cy,cx,cy));//原图的左下象限（左上坐标0,cy;右下坐标cx,cy+cy）
	Mat q3(magnitude_img,Rect(cx,cy,cx,cy));//原图的右下象限（左上坐标cx,cy;右下坐标cx+cx,cy+cy）

	Mat tmp;
	//左上与右下进行交换
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//右上与左下进行交换
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//访问图像中坐标为（200,200）的像素点的值
	//int i = 200;
	//float* data = magnitude_img.ptr<float>(i);
	//printf("\n%f",data[200]);
	//对得到的对数图进行归一化处理
	normalize(magnitude_img,magnitude_img,0,1,CV_MINMAX);

	imshow("the magnitude strumple",magnitude_img);
	waitKey(0);

	return 0;
}