#include "EyeDetector.h"
#include "../utils/MessageUtils.h"

#include <iostream>
namespace EyeDetect {

    void detectAndDrawCircles(cv::Mat& imgSource, cv::Mat& imgProcessed, float inverseRatio, int minDistDiv, int param1,
        int param2, int minRadius, int maxRadius, const std::string& stage, const cv::Scalar& circleColor)
    {
        // Define a vector to store the detected circles.
        std::vector<cv::Vec3f> detectedCircles;

        // Detect circles using the Hough transform.
        HoughCircles(imgProcessed, detectedCircles, cv::HOUGH_GRADIENT, inverseRatio, minDistDiv, param1, param2, minRadius, maxRadius);

        size_t numDetectedCircles = detectedCircles.size();

        // Iterate over each detected circle.
        for (size_t circleIndex = 0; circleIndex < detectedCircles.size(); circleIndex++)
        {
            // Extract the circle parameters: center coordinates and radius
            cv::Vec3i circleParams = detectedCircles[circleIndex];
            cv::Point center = cv::Point(circleParams[0], circleParams[1]); // [0] = Xcenter, [1] = Ycenter

            // Draw a center point for the current circle
            // using the specified colour with a thickness of 1px.
            int lineThickness = 1;
            int centerPointRadius = 1;
            circle(imgSource, center, centerPointRadius, circleColor, lineThickness, cv::LINE_AA);

            // Extract the radius of the current circle
            int radius = circleParams[2]; // [2] = the radius.

            // Draw the outline of the current circle
            // using the center, radius, and specified color with a thickness of 2 pixels
            circle(imgSource, center, radius, circleColor, lineThickness, cv::LINE_AA);

            PrintMessages::PrintCircleCoordinates(stage, center.x, center.y, radius);
        }

        // Print the number of detected circles
        std::cout << "Number of " << stage << " circles detected: " << numDetectedCircles << std::endl;
    }

} //  namespace EyeDetect