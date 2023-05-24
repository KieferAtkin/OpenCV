#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Image Resize and Crop //////////////////////

void main()
{
	string sourcePath = "Resources/TestImage.png";
	Mat imageSource = imread(sourcePath);
	Mat imageResized, imageCropped;

	// cout << imageSource.size() << endl;
	resize(imageSource, imageResized, Size(), 0.5, 0.5);

	Rect regionOfInterest(100, 100, 350, 250);
	imageCropped = imageSource(regionOfInterest);

	imshow("Image", imageSource);
	imshow("Image Resized", imageResized);
	imshow("Imaged Cropped", imageCropped);

	waitKey(0);
}