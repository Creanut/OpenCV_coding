#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat image(600,600,CV_8UC3);
	RNG& rng = theRNG();

	while(1)
	{
		char key;
		int count = (unsigned)rng % 100 + 30;
		vector<Point> points;

		for(int i = 0;i < count;i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4,image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4,image.rows * 3 / 4);

			points.push_back(point);
		}

		vector<int> hull;
		convexHull(Mat(points),hull,true);

		image = Scalar::all(0);
		for(int i = 0;i < count;i++)
		{
			circle(image,points[i],3,Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),1,8);
			int hullcount = (int)hull.size();
			Point point0 = points[hull[hullcount - 1]];

			for(int i = 0;i < hullcount;i++)
			{
				Point point = points[hull[i]];
				line(image,point0,point,Scalar(255,255,255),2,8);
				point0 = point;
			}
			imshow("the result image",image);

			key = (char)waitKey();
			if(key == 27 || key == 'q' || key == 'Q')
				break;
		}
		return 0;
	}
}