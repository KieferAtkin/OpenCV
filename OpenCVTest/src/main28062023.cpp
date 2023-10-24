#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#include "../utils/MessageUtils.h"
#include "../utils/image_utils.h"
#include "Processing.h"
#include "EyeDetector.h"

using namespace cv;
using namespace std;

/* Colours */
cv::Scalar Purple(255, 0, 255);
cv::Scalar Yellow(0, 255, 255);


cv::Mat ProcessImageForPupil(const cv::Mat& inputImage) 
{
    /*** Pupil Boundry ***/
    cv::Size pupil_BlurKernelSize(5, 5);
    double pupil_blurSigmaX = 1.4;
    double pupil_blurSigmaY = 0; // if 0 then it uses the same as SigmaX
    int pupil_CannyThreshold1 = 0;
    int pupil_CannyThreshold2 = 75;
    int pupil_sobelApetureSize = 3;

    // Process the image for pupil boundry
    cv::Mat processedImage = ImgProcess::ProcessImage(inputImage, pupil_BlurKernelSize, pupil_blurSigmaX, pupil_blurSigmaY,
        pupil_CannyThreshold1, pupil_CannyThreshold2, pupil_sobelApetureSize, "Pupil Boundry");

    return processedImage;
}

cv::Mat ProcessImageForLimbal(const cv::Mat& inputImage) 
{
    /*** Limbal Boundry ***/
    cv::Size iris_BlurKernelSize(5, 5);
    double iris_blurSigmaX = 1.4;
    double iris_blurSigmaY = 0; // if 0 then it uses the same as SigmaX
    int iris_CannyThreshold1 = 16;
    int iris_CannyThreshold2 = 38;
    int iris_sobelApetureSize = 3;

    // Process the image for Limbic Boundry.
    cv::Mat processedImage2 = ImgProcess::ProcessImage(inputImage, iris_BlurKernelSize, iris_blurSigmaX, iris_blurSigmaY,
        iris_CannyThreshold1, iris_CannyThreshold2, iris_sobelApetureSize,
        "Limbal Boundry");

    return processedImage2;
}

void DetectAndDrawPupilBoundary(cv::Mat& imgSource, cv::Mat& processedImage)
{
    /* Hough Pupil Boundry */
    double pupil_InverseRatio = 1.0;
    double pupil_Param1 = 5; // to do with Canny.
    double pupil_Param2 = 50; // Threshold for the circle centers at the detection stage ( lower = more likely to have false circles).
    double pupil_MinDistDiv = 1000; // Minimum distance between the centers of the detected circles.
    int pupil_MinRadius = 50;
    int pupil_MaxRadius = 200;

    // Detect and draw the pupil boundry.
    EyeDetect::detectAndDrawCircles(imgSource, processedImage, pupil_InverseRatio,
        pupil_MinDistDiv, pupil_Param1, pupil_Param2,
        pupil_MinRadius, pupil_MaxRadius, "Pupil Boundry", Yellow);
}

void DetectAndDrawLimbalBoundry(cv::Mat& imgSource, cv::Mat processedImage2) 
{
    /* Hough Limbal Boundry */
    double iris_InverseRatio = 1.0;
    double iris_Param1 = 38; // specifies the max threshold value it will use for its canny. then Min is half the max.
    double iris_Param2 = 67; // Threshold for the circle centers at the detection stage ( lower = more likely to have false circles).
    double iris_MinDistDiv = 1000; // Minimum distance between the centers of the detected circles. // was imgProcessed.rows / minDistDiv as the parameter
    int iris_MinRadius = 120;
    int iris_MaxRadius = 250;

    EyeDetect::detectAndDrawCircles(imgSource, processedImage2, iris_InverseRatio,
        iris_MinDistDiv, iris_Param1, iris_Param2,
        iris_MinRadius, iris_MaxRadius, "Limbic Boundry", Purple);

}


void main()
{
    Mat imgLoaded, imgGray;
    std::string imgPath = "Resources/EyeSignImages/TestImages2.bmp";

    // load the Source image.
    ImgUtils::LoadImageFromFile(imgPath, imgLoaded);
        
    cv::Mat imgSource = imgLoaded;
   
    // Convert the source image to grayscale.
    cvtColor(imgSource, imgGray, COLOR_BGR2GRAY);

    // Process prep image for Pupil.
    cv::Mat processedImage = ProcessImageForPupil(imgGray);
    imshow("Pupil Boundry: Processed Image Output", processedImage);
    
    // Detect and draw the pupil boundary.
    DetectAndDrawPupilBoundary(imgSource, processedImage);
    
    // Process prep image for Limbal.
    cv::Mat processedImage2 = ProcessImageForLimbal(imgGray);
    imshow("Limbic Boundry: Processed Image Output", processedImage2);

    // Detect and draw the limbic Boundry.
    DetectAndDrawLimbalBoundry(imgSource, processedImage2);

    imshow("detected circles", imgSource);
    waitKey(0);
}

//
//// Dilate the edges to connect nearby features
//int dilationSize = 3; // Adjust this size as needed
//Mat dilatedEdges;
//dilate(edges, dilatedEdges, getStructuringElement(MORPH_RECT, Size(dilationSize, dilationSize)));
//
//// Find contours
//std::vector<std::vector<Point>> contours;
//findContours(dilatedEdges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//
//// Draw eyelash contours
//drawContours(image, contours, -1, Purple, 1);
//
//
//// Apply thresholding to segment the eyelids
//Mat thresholded;
//threshold(blurred, thresholded, 125, 255, THRESH_BINARY);
//
//// Find contours of the segmented regions
//std::vector<std::vector<Point>> eyelidContours;
//findContours(thresholded, eyelidContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//// Filter contours based on area or length to exclude noise
//std::vector<std::vector<Point>> filteredEyelidContours;
//double minContourArea = 100.0; // Adjust this area threshold as needed
//for (const auto& contour : eyelidContours) {
//    if (contourArea(contour) > minContourArea)
//        filteredEyelidContours.push_back(contour);
//}
//
//// Draw eyelid contours
//drawContours(image, filteredEyelidContours, -1, Scalar(0, 255, 0), FILLED);
