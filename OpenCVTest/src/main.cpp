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

cv::Scalar Purple(255, 0, 255);

cv::Mat ProcessImageForEyeLid(const cv::Mat& inputImage)
{
    /*** Limbal Boundry ***/
    cv::Size iris_BlurKernelSize(7, 7);
    double iris_blurSigmaX = 0;
    double iris_blurSigmaY = 0; // if 0 then it uses the same as SigmaX
    int iris_CannyThreshold1 = 20;
    int iris_CannyThreshold2 = 60;
    int iris_sobelApetureSize = 3;

    // Process the image for Limbic Boundry.
    cv::Mat processedImage2 = ImgProcess::ProcessImage(inputImage, iris_BlurKernelSize, iris_blurSigmaX, iris_blurSigmaY,
        iris_CannyThreshold1, iris_CannyThreshold2, iris_sobelApetureSize,
        "EyeLid / EyeLash Detection");

    return processedImage2;
}


void main() {


    
    Mat image = imread("Resources/EyeSignImages/TestImages5.bmp");

    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    Mat blurred;
    GaussianBlur(gray, blurred, Size(7,7),0);


    double x = 10;
    double y = 60
        ;


    // Apply edge detection to detect eyelashes
    Mat edges;
    Canny(blurred, edges, x, y);


    imshow("edgesEyelashes", edges);

    // Dilate the edges to connect nearby features
    int dilationSize = 3; // Adjust this size as needed
    Mat dilatedEdges;
    dilate(edges, dilatedEdges, getStructuringElement(MORPH_RECT, Size(dilationSize, dilationSize)));

    // Find contours
    std::vector<std::vector<Point>> contours;
    findContours(dilatedEdges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Draw eyelash contours
    drawContours(image, contours, -1, Purple, 1);





    


    // Display the result
    imshow("Eyelashes and eyelids", image);
    waitKey(0);

}