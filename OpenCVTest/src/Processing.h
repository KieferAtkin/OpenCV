#ifndef PROCESSING_H
#define PROCESSING_H

#include "opencv2/opencv.hpp"

namespace ImgProcess 
{
	cv::Mat CalculateGradient(const cv::Mat& input);

	cv::Mat DilateImage(const cv::Mat& input, const std::string stage);

	cv::Mat ProcessImage(cv::Mat imgSource, cv::Size blurKernelSize, double blurSigmaX, double blurSigmaY,
		int cannyThreshold1, int cannyThreshold2, int sobelApetureSize, const static std::string stage);

	cv::Mat ProcessImageFilter(cv::Mat imgSource, cv::Size blurKernelSize, double blurSigmaX, double blurSigmaY,
		int cannyThreshold1, int cannyThreshold2, int sobelApetureSize, const static std::string stage);

} // ImgProcess

#endif // PROCESSING_H