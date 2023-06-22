#include "MessageUtils.h"
#include <iostream>
#include <sstream>

namespace PrintMessages 
{
    void PrintImageResolution(int width, int height) {
        // Create a stringstream using the message template
        std::stringstream messageStream(imageResolutionMessage);
        // Convert the stringstream to a string
        std::string message = messageStream.str();

        // Find the positions of the width and height placeholders in the message
        size_t widthPlaceholderPos = message.find("{width}");
        size_t heightPlaceholderPos = message.find("{height}");

        // Replace the width placeholder with the provided width value
        message.replace(widthPlaceholderPos, std::string("{width}").size(), std::to_string(width));

        // Adjust the height placeholder position based on the change in width length
        heightPlaceholderPos += std::to_string(width).size() - std::string("{width}").size();

        // Replace the height placeholder with the provided height value
        message.replace(heightPlaceholderPos, std::string("{height}").size(), std::to_string(height));

        // Print the updated message to the console
        std::cout << message << std::endl;
    }

    void PrintCircleCoordinates(const std::string& boundaryType, int x, int y, int radius) {
        // Create a copy of the message template
        std::string message = boundaryMessageTemplate;

        // Find the positions of the placeholders in the message template
        size_t boundaryPos = message.find("{BoundaryType}");
        size_t xPos = message.find("{x}");
        size_t yPos = message.find("{y}");
        size_t radiusPos = message.find("{radius}");

        // Replace the boundary type placeholder with the provided boundary type
        message.replace(boundaryPos, std::string("{BoundaryType}").size(), boundaryType);

        // Calculate the change in length for boundary, x, y, and radius
        size_t boundaryLengthChange = boundaryType.size() - std::string("{BoundaryType}").size();
        size_t xLengthChange = std::to_string(x).size() - std::string("{x}").size();
        size_t yLengthChange = std::to_string(y).size() - std::string("{y}").size();
        size_t radiusLengthChange = std::to_string(radius).size() - std::string("{radius}").size();

        // Adjust the positions based on the change in length
        xPos += boundaryLengthChange;
        yPos += boundaryLengthChange + xLengthChange;
        radiusPos += boundaryLengthChange + xLengthChange + yLengthChange;

        // Replace the x-coordinate, y-coordinate, and radius placeholders with the provided values
        message.replace(xPos, std::string("{x}").size(), std::to_string(x));
        message.replace(yPos, std::string("{y}").size(), std::to_string(y));
        message.replace(radiusPos, std::string("{radius}").size(), std::to_string(radius));

        // Print the updated message to the console
        std::cout << message << std::endl;
    }

    void PrintImageLoadError() {
        std::cout << imageLoadErrorMessage << std::endl;
    }

    void PrintImageLoadSuccess() {
        std::cout << imageLoadSuccessMessage << std::endl;
    }
}
