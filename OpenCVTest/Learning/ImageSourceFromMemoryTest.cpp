#include <opencv2/opencv.hpp>

// Function to load an image from a memory address
cv::Mat loadImageFromMemory(const unsigned char* imageData, size_t imageSize)
{
    std::vector<unsigned char> buffer(imageData, imageData + imageSize);
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    return image;
}

int main()
{
    // Example memory address and size
    const unsigned char* imageData = /* Your memory address */;
    size_t imageSize = /* Size of the image data */;

    // Load the image from memory
    cv::Mat imageSource = loadImageFromMemory(imageData, imageSize);

    // Use the loaded image as needed
    // ...

    return 0;
}
