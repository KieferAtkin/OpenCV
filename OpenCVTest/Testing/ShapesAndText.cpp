#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////  Image Resize and Crop //////////////////////

void main()
{
	// Bank Image
	Mat imageBlank(512,
		512,
		CV_8UC3,
		Scalar(255, 255, 255)); // Blue,Green,Red.

	//circle(imageBlank, Point(256, 256), 155, Scalar(0, 69, 255), 10);
	//circle(imageBlank, Point(256, 256), 79, Scalar(147, 144, 0), 10);
	//circle(imageBlank, Point(128, 128), 155, Scalar(0, 69, 255), 20);
	//circle(imageBlank, Point(128, 128), 79, Scalar(147, 144, 0), 10);
	//circle(imageBlank, Point(128, 300), 155, Scalar(0, 69, 255), 5);
	//circle(imageBlank, Point(300, 128), 79, Scalar(147, 144, 0), 10);


	circle(imageBlank, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);
	rectangle(imageBlank, Point(130, 226), Point(382, 286), Scalar(255, 255, 255),FILLED);
	line(imageBlank, Point(130, 296), Point(382, 296), Scalar(255, 255, 255),2);

	putText(imageBlank, "IrisGuard OpenCV", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(147, 144, 0), 1.5);
	

	
	imshow("Image", imageBlank);

	waitKey(0);
}