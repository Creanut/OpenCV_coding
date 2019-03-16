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
	//Ϊ����Ҷ�任�������洢�ռ�
	/*����Ҷ�任�Ľ��Ϊ��������ÿһ�����ص�ı任���������ʵ�����ֺ��������֣��������������ͼ��ֵ
	 ����Ƶ��ֵ��ΧԶԶ�����ռ�ֵ��Χ�������Ҫ��Ƶ��ֵ�洢��float��ʽ�У�����Ҫ��ԭͼ��ֵת��Ϊfloat���ͣ�
	 ����ΪƵ��ֵ�Ĵ洢�ռ䣬������Ҫ��������һ��ͨ���Դ洢����*/
	Mat planes_1 ;
	padded.convertTo(planes_1,CV_32F);
	Mat planes_2 = Mat::zeros(padded.size(),CV_32F);
	Mat planes[] = {planes_1,planes_2};
	Mat complex_i;
	merge(planes,2,complex_i);


	dft(complex_i,complex_i);

	split(complex_i,planes);//��ʵ�����鲿�ֿ�
	magnitude(planes[0],planes[1],planes[0]);//�����ֵ��������ֵ�������洢��planes[0]��
	Mat magnitude_img = planes[0];//�õ���ֵ����
	//imshow("the magnitude image",magnitude_img);

	//���ж����߶ȵ����ţ����㹫ʽ��M=log(1+M)
	magnitude_img += Scalar::all(1);
	log(magnitude_img,magnitude_img);
	//imshow("the magnitude image",magnitude_img);
	//����ֵ��-2����&���㣬�õ��Ľ�����ҵ������������������ż��ֵ���˴�����������������л��������У����Ƶ�׽��м���
	magnitude_img = magnitude_img(Rect(0,0,magnitude_img.cols & -2,magnitude_img.rows & -2));
	//normalize(magnitude_img,magnitude_img,0,1,CV_MINMAX);
	//imshow("the middle image",magnitude_img);

	//int test_m = 77;
	//int test_n = 90;

	//printf("%d,%d",(test_m & -2),(test_n & -2));

	int cx = magnitude_img.cols/2;
	int cy = magnitude_img.rows/2;
	Mat q0(magnitude_img,Rect(0,0,cx,cy));//ԭͼ���������ޣ���������0,0����������cx,cy��
	Mat q1(magnitude_img,Rect(cx,0,cx,cy));//ԭͼ���������ޣ���������cx,0;��������cx,cy��
	Mat q2(magnitude_img,Rect(0,cy,cx,cy));//ԭͼ���������ޣ���������0,cy;��������cx,cy+cy��
	Mat q3(magnitude_img,Rect(cx,cy,cx,cy));//ԭͼ���������ޣ���������cx,cy;��������cx+cx,cy+cy��

	Mat tmp;
	//���������½��н���
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//���������½��н���
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//����ͼ��������Ϊ��200,200�������ص��ֵ
	//int i = 200;
	//float* data = magnitude_img.ptr<float>(i);
	//printf("\n%f",data[200]);
	//�Եõ��Ķ���ͼ���й�һ������
	normalize(magnitude_img,magnitude_img,0,1,CV_MINMAX);

	imshow("the magnitude strumple",magnitude_img);
	waitKey(0);

	return 0;
}