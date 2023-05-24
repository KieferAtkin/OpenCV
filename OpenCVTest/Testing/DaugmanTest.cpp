#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


Mat imageDetectedEdges;
Mat imageGaussianBlur;
Mat imageDilated;

/******** Gaussian ************/
int gaussianKernelFilterWidth = 3;
int gaussianKernalFilterHeight = 3;
double gaussianDeviationOnX = 2;
double gaussianDeviationOnY = 2;

/*********** Canny ************/
int lowThreshold = 0;
const int max_lowThreshold = 100;
const double thresholdRatio = 3;
const int kernel_size = 3; // the size of the Sobel kernel to be used internally

/********** dilated **********/


/********** Hough ************/
int inverseRatio = 1;
int hough_Min_Threshold = 33;
int hough_Max_Threshold = 180;
int hough_Min_Distance = 16;
int hough_min_Radius = 50;
int hough_max_Radius = 150;

void main()
{
    //string imagePath = "Resources/EyeSignImages/Smarties.jpg";
    //string imagePath = "Resources/EyeSignImages/Name6.bmp";
    string imagePath = "Resources/EyeSignImages/TestImages2.bmp";
    
    // Loads an image and convert to grayscale.
    Mat imageSourceGray = imread(imagePath, IMREAD_GRAYSCALE);
    cout << "loaded Image" << endl;

    GaussianBlur(imageSourceGray, 
                 imageGaussianBlur, 
                 Size(gaussianKernelFilterWidth, gaussianKernalFilterHeight),
                 gaussianDeviationOnX,
                 gaussianDeviationOnY,
                 BORDER_DEFAULT);
   
    Canny(imageGaussianBlur,
          imageDetectedEdges,
          lowThreshold,
          lowThreshold * thresholdRatio,
          kernel_size);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imageDetectedEdges, imageDilated, kernel);

    imshow("Gaussian Image", imageGaussianBlur);
    imshow("Detected Image", imageDetectedEdges);
    imshow("Dilated Image", imageDilated);

    //std::vector<Vec3f> circles;
    //HoughCircles(imageDetectedEdges,             // Input
    //    circles,                                 // Output
    //    HOUGH_GRADIENT,                          // Detection method
    //    inverseRatio,                            // Inverse ratio of the accumulator resolution to the image resolution. 
    //    imageDetectedEdges.rows / hough_Min_Distance,  // change this value to detect circles with different distances to each other
    //    hough_Max_Threshold,
    //    hough_Min_Threshold,
    //    hough_min_Radius,
    //    hough_max_Radius
    //);

    ///*
    //// Perform Hough Circle transform
    //std::vector<Vec3f> circles;
    //HoughCircles(imageDetectedEdges, circles, HOUGH_GRADIENT, 1, imageDetectedEdges.rows / 8, 200, 100, 0, 0);
    //*/

    //
    //// Iterate through detected circles
    //for (size_t i = 0; i < circles.size(); i++)
    //{
    //    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    //    int radius = cvRound(circles[i][2]);

    //    // Draw the circle on the original image
    //    circle(imageSourceGray, center, radius, Scalar(0, 255, 0), 2);
    //}

    waitKey(0);

   
}
