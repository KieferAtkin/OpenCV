#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat imageDetectedEdges;
Mat imageGaussianBlur;
Mat imageDilated;

/********** dilated **********/
int dilationKernelColumn = 2;
int dilationKernelRow = 2;

static void LoadImageFromPath(Mat& imageSourceGray)
{
    //string imagePath = "Resources/EyeSignImages/Smarties.jpg";
    //string imagePath = "Resources/EyeSignImages/Name6.bmp";
    string imagePath = "Resources/EyeSignImages/TestImages2.bmp";
   

    // Loads image and converts.
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
    cvtColor(imageLoaded, imageLoaded, COLOR_BGR2GRAY);

   // imshow("imageLoaded Window", imageLoaded);
   ///*
   // /******** Gaussian ************/
   // int gaussianKernelFilterWidth = 3;
   // int gaussianKernalFilterHeight = 3;
   // double gaussianDeviationOnX = 2;
   // double gaussianDeviationOnY = 2;

   // GaussianBlur(imageLoaded, 
   //              imageGaussianBlur,
   //              Size( gaussianKernelFilterWidth, 
   //                    gaussianKernalFilterHeight),
   //              gaussianDeviationOnX, 
   //              gaussianDeviationOnY, 
   //              BORDER_DEFAULT);

   // imshow("imageGaussianBlur Window", imageGaussianBlur);

   // /*********** Canny ************/
   // int threshold1 = 25; // 1st threshold for histeresis
   // const double thresholdRatio = 3;
   // //int threshold2 = threshold1 * thresholdRatio; // 2nd threshold for histeresis
   // int threshold2 = 75;
   // const int cannyKernel = 3; // the size of the Sobel kernel to be used internally

   // Canny(imageGaussianBlur, imageDetectedEdges, threshold1, threshold2, cannyKernel);
   // imshow("imageDetectedEdges Window", imageDetectedEdges);
   //
    Mat imageMedianBlur, imageDilated;
    medianBlur(imageLoaded, imageMedianBlur, 5);
    Canny(imageMedianBlur, imageDetectedEdges, 25, 75);

    
       
    /********** Hough ************/
    double inverseRatio = 1;
    double min_dist = 16;  // Minimum distance between detected centers.
    double param_1 = 33;          // Upper threshold for the internal Canny edge detector
    double param_2 = 180;           // Threshold for center detection
    int min_radius = 80;               // Minimum radius to be detected. If unknown, put zero as default.
    int max_radius = 150;              // Maximum radius to be detected. If unknown, put zero as default.
        
    // Perform Hough Circle transform
    std::vector<Vec3f> circles;
    HoughCircles(imageDetectedEdges,
                 circles, 
                 HOUGH_GRADIENT, 
                 inverseRatio,
                 imageDetectedEdges.rows / 
                 min_dist,
                 param_1, 
                 param_2,
                 min_radius,
                 max_radius);

        std::cout << "Circle Size:" << "    " << circles.size() << "      " << "Px" << std::endl;

        
    // Iterate through detected circles
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        circle(imageLoaded, center, 1, Scalar(255, 255, 0), 2, LINE_AA);

        int radius = cvRound(circles[i][2]);
        std::cout << "Circle radius:" << "    " << radius << "      " << "Px" << std::endl;
        // Draw the circle on the original image
        circle(imageLoaded, center, radius, Scalar(255, 100, 255), 2);
    }
    
    imshow("Detect Circles", imageDetectedEdges);
    //imshow("imageDetectedEdges Window", imageDetectedEdges);
    
   waitKey(0);

}
