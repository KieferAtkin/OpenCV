#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"

namespace ImgUtils
{
	cv::Size GetResolution(const cv::Mat& image);

	void LoadImageFromFile(const std::string imgPath, cv::Mat& img);

	std::string generateFileName(const std::string& folderPath, const std::string& extension, const std::string& stage);

	void saveImageWithGeneratedName(const cv::Mat& image, const std::string& folderPath, const std::string& extension, const std::string& stage);

} // namespace ImgUtils

#endif // IMAGE_UTILS_H
