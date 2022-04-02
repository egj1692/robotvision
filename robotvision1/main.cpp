#include<iostream>
#include<filesystem>
#include<vector>
#include<time.h>
#include<math.h>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Mat kmeans_clustering(Mat img, int k);

int main() {
	srand((unsigned int)time(NULL));
	String path = "./data/";
	Mat img_1 = imread(path + "2apples");
	Mat img_2 = imread(path + "2or4objects");
	Mat img_3 = imread(path + "7apples");
	Mat img_4 = imread(path + "colors"); 
	Mat img_5 = imread(path + "variableObjects");

	kmeans_clustering(img_1, 3);
	return 0;
}

Mat kmeans_clustering(Mat img, int k) 
{
	Mat result = Mat::zeros(img.size(), CV_8UC3);

	// 이미지 픽셀값을 좌표값을로 변환
	vector<Point3f> point;
	int offset;
	uchar* img_data = img.data;
	for (int r = 0; r < img.rows; r++) {
		/* uchar* pointer_row = img.ptr<uchar>(r); */
		for (int c = 0; c < img.cols; c++) {
			/*
			uchar b = pointer_row[c * 3 + 0];
			uchar g = pointer_row[c * 3 + 1];
			uchar r = pointer_row[c * 3 + 2];
			*/
			
			uchar b = img_data[r * img.cols * 3 + c * 3];
			uchar g = img_data[r * img.cols * 3 + c * 3 + 1];
			uchar r = img_data[r * img.cols * 3 + c * 3 + 2];
			point.push_back(Point3f(b, g, r));
		}
	}

	// 랜덤으로 중심 생성
	vector<Point3f> center;
	for (int i = 0; i < k; i++)
	{
		int b = rand() % 256;
		int g = rand() % 256;
		int r = rand() % 256;
		center.push_back(Point3f(b, g, r));
	}

	vector<vector<int>> center_asign(center.size());
	vector<Point3f> tmp_center = { center.begin(), center.end() };
	bool same = false;
	// 반복
	do {
		for (int i = 0; i < point.size(); i++)
		{
			double min = 1000;
			int center_num = -1;
			for (int j = 0; j < tmp_center.size(); j++)
			{
				double dis = 0;
				dis = sqrt(pow(tmp_center[j].x - point[i].x, 2) + pow(tmp_center[j].y - point[i].y, 2) + pow(tmp_center[j].z - point[i].z, 2));
				if (dis < min)
				{
					dis = min;
					center_num = j;
				}
			}
			center_asign[center_num].push_back(i);
		}

		for (int i = 0; i < k; i++)
		{
			int tmp_x = 0, tmp_y = 0, tmp_z = 0;
			for (int j = 0; j < center_asign[i].size(); j++)
			{
				tmp_x += point[j].x;
				tmp_y += point[j].y;
				tmp_z += point[j].z;
			}
			tmp_center[i].x = tmp_x / center_asign[i].size();
			tmp_center[i].y = tmp_y / center_asign[i].size();
			tmp_center[i].z = tmp_z / center_asign[i].size();
		}
		center == tmp_center ? 	same = true : same = false;
		
	} while (same == true);


	return result;
}