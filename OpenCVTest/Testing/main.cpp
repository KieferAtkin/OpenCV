#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#include "MessageUtils.h"

using namespace cv;
using namespace std;

/********** back up hough ********/
//int inverseRatio = 1;
//int hough_Min_Threshold = 33;
//int hough_Max_Threshold = 180;
//int hough_Min_Distance = 16;
//int hough_min_Radius = 50;
//int hough_max_Radius = 150;

/* pupil boundry */
double pupil_inverseRatio = 1.0;
double pupil_param_1 = 30; // to do with Canny.
double pupil_param_2 = 50; // accuracy : lower is less good
double pupil_min_dist_div = 8; // For some reason the lower the number the better the result. Could result in false.
int pupil_min_radius = 50;
int pupil_max_radius = 200;

/* iris boundry */
double iris_inverseRatio = 1.0;
double param_1 = 30; // to do with Canny.
double param_2 = 50; // accuracy : lower is less good
double iris_min_dist_div = 8; // For some reason the lower the number the better the result. Could result in false.
int min_radius = 100;
int max_radius = 300;

cv::Size GetResolution(const cv::Mat& image)
{
    int width = image.cols;
    int height = image.rows;

    return cv::Size(width, height);
}

static void LoadImageSource(cv::Mat& imageSource)
{
    std::string imagePath = "Resources/EyeSignImages/TestImages2.bmp";

    // Load image wether its colour or not.
    imageSource = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (imageSource.empty()) {

        PrintMessages::PrintImageLoadError();
        return;
    }

    cv::Size resolution = GetResolution(imageSource);
    int width = resolution.width;
    int height = resolution.height;
    PrintMessages::PrintImageResolution(width, height);

    PrintMessages::PrintImageLoadSuccess();
}

void detectAndDrawCircles(Mat& imgSource, Mat& imgDilated, float inverseRatio, int minDistDiv, int param1, int param2, int minRadius, int maxRadius, const string& circleType, const Scalar& circleColor)
{
    // Define a vector to store the detected circles
    vector<Vec3f> detectedCircles;

    // Detect circles using the Hough transform
    HoughCircles(imgDilated, detectedCircles, HOUGH_GRADIENT, inverseRatio, imgDilated.rows / minDistDiv, param1, param2, minRadius, maxRadius);

    // Variable to store the number of detected circles
    size_t numDetectedCircles = detectedCircles.size();

    // Iterate over each detected circle
    for (size_t circleIndex = 0; circleIndex < detectedCircles.size(); circleIndex++)
    {
        // Extract the circle parameters: center coordinates and radius
        Vec3i circleParams = detectedCircles[circleIndex];
        Point center = Point(circleParams[0], circleParams[1]); // [0] = Xcenter, [1] = Ycenter

        // Draw a small circle at the center of the current circle
        // using the specified color with a thickness of 2 pixels
        circle(imgSource, center, 1, circleColor, 2, LINE_AA);

        // Extract the radius of the current circle
        int radius = circleParams[2]; // [2] = the radius.

        // Draw the outline of the current circle
        // using the center, radius, and specified color with a thickness of 2 pixels
        circle(imgSource, center, radius, circleColor, 2, LINE_AA);

        PrintMessages::PrintCircleCoordinates(circleType, center.x, center.y, radius);
    }

    // Print the number of detected circles
    std::cout << "Number of " << circleType << " circles detected: " << numDetectedCircles << std::endl;
}

cv::Mat calculateGradient(const cv::Mat& input)
{
    cv::Mat gradient;

    // Define the kernels for calculating gradient in the X and Y directions
    cv::Mat kernelX = (cv::Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    cv::Mat kernelY = (cv::Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

    // Apply the gradient kernels to the input image
    cv::Mat gradX, gradY;
    cv::filter2D(input, gradX, CV_32F, kernelX);
    cv::filter2D(input, gradY, CV_32F, kernelY);

    // Compute the magnitude of the gradient using the X and Y components
    cv::magnitude(gradX, gradY, gradient);

    return gradient;
}

cv::Mat imageProcessing(cv::Mat imgSource)
{
    cv::Mat imgGaussianBlur;
    cv::Mat imgGradient;
    cv::Mat imgCanny;

    // Apply Gaussian blur to the grayscale image
    cv::GaussianBlur(imgSource, imgGaussianBlur, cv::Size(5, 5), 1.4, 0);
    imshow("Gaussian", imgGaussianBlur);

    // Calculate gradient using the intensity gradient filter
    imgGradient = calculateGradient(imgGaussianBlur);

    // Convert the gradient image to 8-bit
    imgGradient.convertTo(imgGradient, CV_8U);
    imshow("Gradient", imgGradient);

    // Perform Canny edge detection on the gradient image
    cv::Canny(imgGaussianBlur, imgCanny, 0, 75, 3);
    imshow("Canny", imgCanny);

   return imgCanny;
}

void main()
{
    Mat imgLoaded, imgGray;

    LoadImageSource(imgLoaded);
    cv::Mat imgSource = imgLoaded;
   
    // Convert the source image to grayscale
    cvtColor(imgSource, imgGray, COLOR_BGR2GRAY);


    // Call the imageProcessing function to process the image
    cv::Mat processedImage = imageProcessing(imgGray);
    
    // Call the function for the "Pupil" circles
    detectAndDrawCircles(imgSource, processedImage, pupil_inverseRatio,
                         pupil_min_dist_div, pupil_param_1, pupil_param_2, 
                         pupil_min_radius, pupil_max_radius, "Pupil", Scalar(0, 255, 255));

    // Call the function for the "Limbic" circles
    detectAndDrawCircles(imgSource, processedImage, iris_inverseRatio,
                         iris_min_dist_div, param_1, param_2, 
                         min_radius, max_radius, "Limbic", Scalar(255, 0, 255));

    imshow("detected circles", imgSource);
    
    
    waitKey(0);

}