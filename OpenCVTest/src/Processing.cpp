#include "Processing.h"

namespace ImgProcess {


cv::Mat CalculateGradient(const cv::Mat& input)
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

cv::Mat DilateImage(const cv::Mat& input, const std::string stage)
{
    cv::Mat imgDilated;
    cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));

    cv::dilate(input, imgDilated, structuringElement);
    imshow(stage + ": " + "Dilated", imgDilated);

    return imgDilated;
}

cv::Mat ProcessImage(cv::Mat imgSource, cv::Size blurKernelSize, double blurSigmaX, double blurSigmaY,
    int cannyThreshold1, int cannyThreshold2, int sobelApetureSize, bool dilate, const static std::string stage)
{
    cv::Mat imgGaussianBlur;
    cv::Mat imgGradient;
    cv::Mat imgCanny;

    // Denoise
    cv::GaussianBlur(imgSource, imgGaussianBlur, blurKernelSize, blurSigmaX, blurSigmaY);
    // imshow( stage + ": " + "Gaussian", imgGaussianBlur);

    // Calculate gradient using the intensity gradient filter
    imgGradient = CalculateGradient(imgGaussianBlur);

    // Convert the gradient image to 8-bit
    imgGradient.convertTo(imgGradient, CV_8U);
    imshow(stage + ": " + "Gradient", imgGradient);

    // Perform Canny edge detection on the gradient image
    cv::Canny(imgGaussianBlur, imgCanny, cannyThreshold1, cannyThreshold2, sobelApetureSize);
    // imshow(stage + ": " + "Canny", imgCanny);

    // Perform dilation if the flag is set to true to the Canny Image.
    if (dilate)
    {
        imgCanny = DilateImage(imgCanny, stage);
    }

    return imgCanny;
}

} // ImgProcess
