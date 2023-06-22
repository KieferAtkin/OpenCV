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


void main (){
// Read the image
Mat image = imread("Resources/EyeSignImages/TestImages4.bmp");

// Convert to grayscale
Mat gray;
cvtColor(image, gray, COLOR_BGR2GRAY);

// Apply Gaussian blur to reduce noise
Mat blurred;
GaussianBlur(gray, blurred, Size(7, 7), 0);

// Apply Canny edge detection
Mat edges;
Canny(blurred, edges, 5, 45,3);
imshow("edgesEyelashes", edges);

// Dilate the edges to connect nearby lashes
int dilationSize = 2; // Adjust this size as needed
Mat dilatedEdges;
dilate(edges, dilatedEdges, getStructuringElement(MORPH_RECT, Size(dilationSize, dilationSize)));

// Find contours
std::vector<std::vector<Point>> contours;
findContours(dilatedEdges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

// Filter contours based on area or length to exclude noise
std::vector<std::vector<Point>> filteredContours;
double minContourLength = 10.0; // Adjust this length threshold as needed
for (const auto& contour : contours) {
    if (contourArea(contour) > minContourLength)
        filteredContours.push_back(contour);
}

// Draw eyelash contours
drawContours(image, filteredContours, -1, Scalar(255, 0, 255), FILLED);

// Display the result
imshow("Eyelashes", image);
waitKey(0);

}


//
///* Hough Pupil Boundry */
//double pupil_InverseRatio = 1.0;
//double pupil_Param1 = 75; // to do with Canny.
//double pupil_Param2 = 50; // Threshold for the circle centers at the detection stage ( lower = more likely to have false circles).
//double pupil_MinDistDiv = 1000; // Minimum distance between the centers of the detected circles.
//int pupil_MinRadius = 50;
//int pupil_MaxRadius = 200;
//
///* Hough Iris Boundry */
//double iris_InverseRatio = 1.0;
//double iris_Param1 = 38; // specifies the max threshold value it will use for its canny. then Min is half the max.
//double iris_Param2 = 67; // Threshold for the circle centers at the detection stage ( lower = more likely to have false circles).
//double iris_MinDistDiv = 1000; // Minimum distance between the centers of the detected circles. // was imgProcessed.rows / minDistDiv as the parameter
//int iris_MinRadius = 120;
//int iris_MaxRadius = 250;
//
//
//
//
//
//
//
//
//void main()
//{
//    
//    Mat imgLoaded, imgGray;
//    std::string imgPath = "Resources/EyeSignImages/TestImages4.bmp";
//
//    // load the Source image.
//    ImgUtils::LoadImageFromFile(imgPath, imgLoaded);
//        
//    cv::Mat imgSource = imgLoaded;
//   
//    // Convert the source image to grayscale.
//    cvtColor(imgSource, imgGray, COLOR_BGR2GRAY);
//
//
//    /*** Pupil Boundry ***/
//    cv::Size pupil_BlurKernelSize(5, 5);
//    double pupil_blurSigmaX = 1.4;
//    double pupil_blurSigmaY = 0; // if 0 then it uses the same as SigmaX
//    int pupil_CannyThreshold1 = 0;
//    int pupil_CannyThreshold2 = 75;
//    int pupil_sobelApetureSize = 3;
//    
//    // Process the image for pupil boundry
//    cv::Mat processedImage = ImgProcess::ProcessImage(imgGray, pupil_BlurKernelSize, pupil_blurSigmaX, pupil_blurSigmaY, 
//        pupil_CannyThreshold1, pupil_CannyThreshold2, pupil_sobelApetureSize, false, "Pupil Boundry");
//    imshow("Pupil Boundry: Processed Image Output", processedImage);
//    
//    // Detect and draw the pupil boundry.
//    EyeDetect::detectAndDrawCircles(imgSource, processedImage, pupil_InverseRatio,
//                         pupil_MinDistDiv, pupil_Param1, pupil_Param2, 
//                         pupil_MinRadius, pupil_MaxRadius, "Pupil Boundry",
//                         Scalar(0, 255, 255));
//
//
//    /*** Limbic Boundry ***/
//    
//    cv::Size iris_BlurKernelSize(5,5);
//    double iris_blurSigmaX = 1.4;
//    double iris_blurSigmaY = 0; // if 0 then it uses the same as SigmaX
//    int iris_CannyThreshold1 = 16;
//    int iris_CannyThreshold2 = 38;
//    int iris_sobelApetureSize = 3;
//
//    // Process the image for Limbic Boundry.
//    cv::Mat processedImage2 = ImgProcess::ProcessImage(imgGray, iris_BlurKernelSize, iris_blurSigmaX, iris_blurSigmaY,
//                                                       iris_CannyThreshold1, iris_CannyThreshold2, iris_sobelApetureSize, 
//                                                       false, "Limbic Boundry");
//    imshow("Limbic Boundry: Processed Image Output", processedImage2);
//
//    // Detect and draw the limbic Boundry.
//    EyeDetect::detectAndDrawCircles(imgSource, processedImage2, iris_InverseRatio,
//                         iris_MinDistDiv, iris_Param1, iris_Param2, 
//                         iris_MinRadius, iris_MaxRadius, "Limbic Boundry", 
//                         Scalar(255, 0, 255));
//
//
//    imshow("detected circles", imgSource);
//    waitKey(0);
//}