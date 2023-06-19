#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#include "MessageUtils.h"

using namespace cv;
using namespace std;



/* Hough Pupil Boundry */
double pupil_InverseRatio = 1.0;
double pupil_Param1 = 75; // to do with Canny.
double pupil_Param2 = 50; // Threshold for the circle centers at the detection stage ( lower = more likely to have false circles).
double pupil_MinDistDiv = 24; // Minimum distance between the centers of the detected circles.
int pupil_MinRadius = 50;
int pupil_MaxRadius = 200;

/* Hough Iris Boundry */
double iris_InverseRatio = 1.0;
double iris_Param1 = 38; // specifies the max threshold value it will use for its canny. then Min is half the max.
double iris_Param2 = 67; // Threshold for the circle centers at the detection stage ( lower = more likely to have false circles).
double iris_MinDistDiv = 24; // Minimum distance between the centers of the detected circles.
int iris_MinRadius = 120;
int iris_MaxRadius = 250;

cv::Size GetResolution(const cv::Mat& image)
{
    int width = image.cols;
    int height = image.rows;

    return cv::Size(width, height);
}

static void LoadImageSource(cv::Mat& imageSource)
{
    std::string imagePath = "Resources/EyeSignImages/TestImages4.bmp";

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

        // Draw a center point for the current circle
        // using the specified colour with a thickness of 1px.
        int lineThickness = 1;
        int centerPointRadius = 1;
        circle(imgSource, center, centerPointRadius, circleColor, lineThickness, LINE_AA);

        // Extract the radius of the current circle
        int radius = circleParams[2]; // [2] = the radius.

        // Draw the outline of the current circle
        // using the center, radius, and specified color with a thickness of 2 pixels
        circle(imgSource, center, radius, circleColor, lineThickness, LINE_AA);

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

cv::Mat performDilate(const cv::Mat& input)
{

    cv::Mat dilatedImage;
    cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));

    cv::dilate(input, dilatedImage, structuringElement);

    return dilatedImage;
}

cv::Mat imageProcessing(cv::Mat imgSource, cv::Size blurKernelSize, double blurSigmaX, double blurSigmaY, 
                        int cannyThreshold1, int cannyThreshold2, int sobelApetureSize, bool dilate)
{
    cv::Mat imgGaussianBlur;
    cv::Mat imgGradient;
    cv::Mat imgCanny;

    // Apply Gaussian blur to the grayscale image
    cv::GaussianBlur(imgSource, imgGaussianBlur, blurKernelSize, blurSigmaX, blurSigmaY);
    //imshow("Gaussian", imgGaussianBlur);

    // Calculate gradient using the intensity gradient filter
    imgGradient = calculateGradient(imgGaussianBlur);

    // Convert the gradient image to 8-bit
    imgGradient.convertTo(imgGradient, CV_8U);
    //imshow("Gradient", imgGradient);

    // Perform Canny edge detection on the gradient image
    cv::Canny(imgGaussianBlur, imgCanny, cannyThreshold1, cannyThreshold2, sobelApetureSize);
    imshow("canny*", imgCanny);


    // Perform dilation if the flag is set to true
    if (dilate) 
    {
        imgCanny = performDilate(imgCanny);
    }
    
    return imgCanny;
}

void main()
{
    Mat imgLoaded, imgGray;

    // load the Source image.
    LoadImageSource(imgLoaded);
    cv::Mat imgSource = imgLoaded;
   
    // Convert the source image to grayscale.
    cvtColor(imgSource, imgGray, COLOR_BGR2GRAY);


    cv::Size pupil_BlurKernelSize(5, 5);
    double pupil_blurSigmaX = 1.4;
    double pupil_blurSigmaY = 0; // if 0 then it uses the same as SigmaX
    int pupil_CannyThreshold1 = 0;
    int pupil_CannyThreshold2 = 75;
    int pupil_sobelApetureSize = 3;
    

    // Process the image for pupil boundry
    cv::Mat processedImage = imageProcessing(imgGray, pupil_BlurKernelSize, pupil_blurSigmaX, pupil_blurSigmaY, 
                                             pupil_CannyThreshold1, pupil_CannyThreshold2, pupil_sobelApetureSize, false);
    //imshow("Canny1", processedImage );
    
    // Detect and draw the pupil boundry.
    detectAndDrawCircles(imgSource, processedImage, pupil_InverseRatio,
                         pupil_MinDistDiv, pupil_Param1, pupil_Param2, 
                         pupil_MinRadius, pupil_MaxRadius, "Pupil", Scalar(0, 255, 255));

    
    cv::Size iris_BlurKernelSize(5,5);
    double iris_blurSigmaX = 1.4;
    double iris_blurSigmaY = 0; // if 0 then it uses the same as SigmaX
    int iris_CannyThreshold1 = 15;
    int iris_CannyThreshold2 = 38;
    int iris_sobelApetureSize = 3;
    // Process the image for Limbic Boundry.
    cv::Mat processedImage2 = imageProcessing(imgGray, iris_BlurKernelSize, iris_blurSigmaX, iris_blurSigmaY, 
                                                iris_CannyThreshold1, iris_CannyThreshold2, iris_sobelApetureSize, false);
    imshow("Canny2", processedImage2);

    // Detect and draw the limbic Boundry..
    detectAndDrawCircles(imgSource, processedImage2, iris_InverseRatio,
                         iris_MinDistDiv, iris_Param1, iris_Param2, 
                         iris_MinRadius, iris_MaxRadius, "Limbic", Scalar(255, 0, 255));


    imshow("detected circles", imgSource);
    waitKey(0);
}