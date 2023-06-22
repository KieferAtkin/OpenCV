#ifndef EYE_DETECT_H
#define EYE_DETECT_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

namespace EyeDetect 
{

    void detectAndDrawCircles(cv::Mat& imgSource, cv::Mat& imgProcessed, float inverseRatio, int minDistDiv, int param1,
        int param2, int minRadius, int maxRadius, const std::string& stage, const cv::Scalar& circleColor);

} // namespace EyeDetect

#endif  // EYE_DETECT_H
