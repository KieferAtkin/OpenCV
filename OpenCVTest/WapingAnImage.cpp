#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////  Images - Basic Functions  //////////////////////

float width = 250, height = 350;
Mat matrix, matrix2, imgWarp,imgWarp2;

void main() {

	string sourcePath = "Resources/cards.jpg";
	Mat imageSource = imread(sourcePath);

	Point2f source[4] = { {529,142}, {771,190}, {405,395}, {674,457} };
	Point2f destin[4] = { {0.0f,0.0f}, {width,0.0f}, {0.0f,height},{width,height} };

	matrix = getPerspectiveTransform(source, destin);
	warpPerspective(imageSource, imgWarp, matrix, Point(width, height));

	Point2f source2[4] = { {738,379}, {1029,438}, {643,711}, {971,783} };
	Point2f destin2[4] = { {0.0f,0.0f}, {width,0.0f}, {0.0f,height},{width,height} };

	matrix2 = getPerspectiveTransform(source2, destin2);
	warpPerspective(imageSource, imgWarp2, matrix2, Point(width, height));


	for (int i = 0; i < 4; i++) 
	{
		circle(imageSource, source[i], 10, Scalar(0, 69, 255), FILLED);
		circle(imageSource, source2[i], 10, Scalar(0, 200, 200), FILLED);
	}
	

	imshow("Image", imageSource);
	imshow("Image Warpped", imgWarp);
	imshow("Image Warpped2", imgWarp2);
	
	waitKey(0);

}