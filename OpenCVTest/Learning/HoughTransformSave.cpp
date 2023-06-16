/*
*
* HoughTransformSave is the first attempt at the hough transform.
* This uses a test image from a EyeTrust 2 / EyeHood. The Image is in grayscale.
*
*/


#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/********** back up hough ********/
//int inverseRatio = 1;
//int hough_Min_Threshold = 33;
//int hough_Max_Threshold = 180;
//int hough_Min_Distance = 16;
//int hough_min_Radius = 50;
//int hough_max_Radius = 150;

int inverseRatio = 1;
int hough_Min_Threshold = 33;
int hough_Max_Threshold = 180;
int hough_Min_Distance = 16;
int hough_min_Radius = 50;
int hough_max_Radius = 180;

int canny_LowThreshold = 0;
const int canny_Max_lowThreshold = 100;
const int cannyRatio = 3;
const int canny_Kernel_Size = 3;

void main()
{
    string imagePath = "Resources/EyeSignImages/TestImages2.bmp";

    // Loads an image
    Mat imageSource = imread(imagePath, IMREAD_COLOR);

    // Check if image is loaded fine
    if (imageSource.empty()) {
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", imagePath);
    }

    Mat imageGray, imageMedianBlur, imageCanny, imageDilated;

    cvtColor(imageSource, imageGray, COLOR_BGR2GRAY);
    medianBlur(imageGray, imageMedianBlur, 5);
    Canny(imageMedianBlur, imageCanny, 25, 75);


    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imageCanny, imageDilated, kernel);

    vector<Vec3f> circles;
    HoughCircles(imageCanny,                   // Input
        circles,                                 // Output
        HOUGH_GRADIENT,                          // Detection method
        inverseRatio,                            // Inverse ratio of the accumulator resolution to the image resolution. 
        imageCanny.rows / hough_Min_Distance,  // change this value to detect circles with different distances to each other
        hough_Max_Threshold,
        hough_Min_Threshold,
        hough_min_Radius,
        hough_max_Radius
    );

    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(imageSource, center, 1, Scalar(100, 0, 200), 2, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(imageSource, center, radius, Scalar(0, 234, 255), 2, LINE_AA);
    }

    imshow("detected circles", imageSource);
    //imshow("image Gray", imageGray);
   // imshow("image median blur", imageMedianBlur);
    imshow("image Canny", imageCanny);
    //imshow("image Dilated", imageDilated);

    waitKey(0);

}