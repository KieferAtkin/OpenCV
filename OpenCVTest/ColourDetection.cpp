#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images - Colour Detection  //////////////////////

Mat imgHSV, mask;
int hueMin = 0, saturationMin = 110, valueMin = 153;
int hueMax = 19, saturationMax = 240, valueMax = 255;

void main() {

	string path = "Resources/lambo.png";
	Mat img = imread(path);
	

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	namedWindow("Trackbars", (640,200));
	createTrackbar("HueMin", "Trackbars", &hueMin, 179);
	createTrackbar("HueMax", "Trackbars", &hueMax, 179);
	createTrackbar("saturation Min", "Trackbars", &saturationMin, 255);
	createTrackbar("saturation Max", "Trackbars", &saturationMax, 255);
	createTrackbar("value Min", "Trackbars", &valueMin, 255);
	createTrackbar("value Max", "Trackbars", &valueMax, 255);
	
	while (true) {
		Scalar lowerLimit(hueMin, saturationMin, valueMin);
		Scalar upperLimit(hueMax, saturationMax, valueMax);
		inRange(imgHSV, lowerLimit, upperLimit, mask);
		
		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);
		waitKey(1);
	}

}