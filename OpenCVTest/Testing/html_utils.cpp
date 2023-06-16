#include "html_utils.h"
#include "datetime_utils.h"
#include <fstream>
#include <iostream>

void saveImageToHTML(const std::string& imagePath, const std::string& outputFilename, const std::string& variables, const std::string& functions)
{
    std::ofstream htmlFile(outputFilename);

    if (!htmlFile.is_open())
    {
        std::cout << "Failed to create HTML file." << std::endl;
        return;
    }

    // HTML template
    std::string htmlTemplate = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Modified Iris Image</title>
        </head>
        <body>
            <h1>Modified Iris Image</h1>
            <img src="%IMAGE_PATH%" alt="Modified Iris Image">
            <p>Variables: %VARIABLES%</p>
            <p>Functions: %FUNCTIONS%</p>
            <p>Timestamp: %TIMESTAMP%</p>
        </body>
        </html>
    )";

    // Replace placeholders with actual values
    std::string htmlContent = htmlTemplate;
    htmlContent.replace(htmlContent.find("%IMAGE_PATH%"), 12, imagePath);
    htmlContent.replace(htmlContent.find("%VARIABLES%"), 11, variables);
    htmlContent.replace(htmlContent.find("%FUNCTIONS%"), 11, functions);
    htmlContent.replace(htmlContent.find("%TIMESTAMP%"), 11, getGMTDateTime());

    // Write content to HTML file
    htmlFile << htmlContent;
    htmlFile.close();

    std::cout << "HTML file saved as: " << outputFilename << std::endl;
}
