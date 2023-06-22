#include "image_utils.h"
#include "datetime_utils.h"
#include "../utils/MessageUtils.h"

namespace ImgUtils 
{
    cv::Size GetResolution(const cv::Mat& image) 
    {
        int width = image.cols;
        int height = image.rows;

        return cv::Size(width, height);
    }

    void LoadImageFromFile(const std::string imgPath, cv::Mat& img) 
    {
        img = cv::imread(imgPath, cv::IMREAD_COLOR);
        if (img.empty()) {

            PrintMessages::PrintImageLoadError();
            return;
        }

        cv::Size resolution = ImgUtils::GetResolution(img);
        int width = resolution.width;
        int height = resolution.height;
        PrintMessages::PrintImageResolution(width, height);

        PrintMessages::PrintImageLoadSuccess();
    }


    std::string generateFileName(const std::string& folderPath, const std::string& extension, const std::string& stage) 
    {
        // Generate timestamp using the getGMTDateTime() function
        std::string timestamp = getGMTDateTime();

        // Create file name using the timestamp, stage, and specified extension
        std::string filename = folderPath + "\\" + stage + "_" + timestamp + extension;

        return filename;
    }

    void saveImageWithGeneratedName(const cv::Mat& image, const std::string& folderPath, const std::string& extension, const std::string& stage) {
        // Generate file name with the specified extension, folder path, and stage
        std::string filename = generateFileName(folderPath, extension, stage);

        // Save the image with the generated file name
        cv::imwrite(filename, image);

        std::cout << "Saved image for " << stage << " stage: " << filename << std::endl;
    }

} // namespace ImageUtils

