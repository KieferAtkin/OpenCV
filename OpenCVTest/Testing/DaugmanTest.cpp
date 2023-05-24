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
const double thresholdRatio = 2;
const int kernel_size = 3; // the size of the Sobel kernel to be used internally

/********** dilated **********/
int dilationKernelColumn = 2;
int dilationKernelRow = 2;

/********** Hough ************/
int inverseRatio = 1;
int hough_Min_Distance_Of_Centers = 8;  // Minimum distance between detected centers.
int hough_Min_Threshold = 100;          // Upper threshold for the internal Canny edge detector
int hough_Max_Threshold = 30;           // Threshold for center detection
int hough_min_Radius = 40;               // Minimum radius to be detected. If unknown, put zero as default.
int hough_max_Radius = 150;              // Maximum radius to be detected. If unknown, put zero as default.


static void LoadImageFromPath(Mat& imageSourceGray)
{
    //string imagePath = "Resources/EyeSignImages/Smarties.jpg";
    //string imagePath = "Resources/EyeSignImages/Name6.bmp";
    string imagePath = "Resources/EyeSignImages/TestImages2.bmp";

    // Loads image and converts to grayscale.
    imageSourceGray = imread(imagePath, IMREAD_COLOR);
    if (imageSourceGray.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
    }
    else
    {
        std::cout << "Image Loaded" << std::endl;
    }
}


void main()
{
    cv::Mat imageSource;
    cv::Mat imageLoaded;
    LoadImageFromPath(imageLoaded);
  
        GaussianBlur(imageLoaded,
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

        Mat dilationKernel = getStructuringElement(MORPH_RECT, Size(dilationKernelColumn, dilationKernelRow));
        dilate(imageDetectedEdges, imageDilated, dilationKernel);

       /* imshow("Dilated Image", imageLoaded);
        imshow("Gaussian Image", imageGaussianBlur);
        imshow("Detected Image", imageDetectedEdges);
        imshow("Dilated Image", imageDilated);*/

        //vector<Vec3f> circles;
        //HoughCircles(imageDetectedEdges,                   // Input
        //    circles,                                 // Output
        //    HOUGH_GRADIENT,                          // Detection method
        //    inverseRatio,                            // Inverse ratio of the accumulator resolution to the image resolution. 
        //    imageDetectedEdges.rows / hough_Min_Distance,  // change this value to detect circles with different distances to each other
        //    hough_Max_Threshold,
        //    hough_Min_Threshold,
        //    hough_min_Radius,
        //    hough_max_Radius
        //);
          
        
    // Perform Hough Circle transform
    std::vector<Vec3f> circles;
    HoughCircles(imageDetectedEdges,
                 circles, 
                 HOUGH_GRADIENT, 
                 1, 
                 imageDetectedEdges.rows / 
                 hough_Min_Distance_Of_Centers,
                 hough_Max_Threshold, 
                 hough_Min_Threshold, 
                 hough_min_Radius, 
                 hough_max_Radius);
        
    // Iterate through detected circles
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        circle(imageLoaded, center, 1, Scalar(255, 255, 0), 2, LINE_AA);

        int radius = cvRound(circles[i][2]);

        // Draw the circle on the original image
        circle(imageLoaded, center, radius, Scalar(255, 100, 255), 2);
    }
    
        imshow("Circles Detected", imageLoaded);
        waitKey(0);

}
