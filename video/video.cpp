#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <iostream> 
#include <string>   
#include <vector>

using namespace cv;
using namespace std;

vector<Mat> objects;	
int object_number = 5;
string filenames[5] = {"arrow.png","square.png","circle.png","star.png","rect.png"};
int x[5] = { -1050, 0, -553, -100, -96 };
int y[5] = {161,392,277,68,20};

float u[5] = {4,6,10,55,50};
float a[5] = {9,5,4,-1,1.5};
int fps = 10;
int duration = 10;
string outuput_file = "video_result.avi";
int frame_width = 1280;
int frame_height = 480;

Mat draw_objects()
{
	Mat blank(frame_height, frame_width, CV_8UC3, Scalar(0, 0, 0));
	
	for (int i = 0; i < object_number; i++)
	{
		for (int k = 0; k < objects[i].rows;k++)
		for (int l = 0; l < objects[i].cols; l++)
		{
			if (k + y[i] >= 0 && k + y[i] < frame_height && l + x[i] >= 0 && l + x[i] < frame_width)
			{
				blank.at<Vec3b>(k + y[i], l + x[i]) = objects[i].at<Vec3b>(k, l);
			}
		}
		float dis = u[i] + a[i] / 2;
		x[i] = x[i] + (int)dis;
		u[i] = u[i] + a[i];
	}
	//imshow("test", blank);
	return blank;
}


int main()
{
	VideoWriter video(outuput_file, CV_FOURCC('M', 'J', 'P', 'G'), fps, Size(frame_width, frame_height), true);
	
	for (int i = 0; i < object_number; i++)
	{
		objects.push_back(imread(filenames[i], 1));
	}

	for (int i = 0; i < 60; i++)
	{
		Mat frame = draw_objects();
		video.write(frame);
		imshow("output",frame);
		//char c = waitKey(500);
		char c = waitKey(1000 / fps);
		if (c == 'p')
			cout << "frame: " << i;
	}
	
	//waitKey(0);
	return 0;
}