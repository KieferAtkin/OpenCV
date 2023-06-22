#ifndef MESSAGE_UTILS_H
#define MESSAGE_UTILS_H

#include <string>

namespace PrintMessages {
    const std::string imageResolutionMessage = R"(
********************************************
                                
  Image resolution: {width} x {height}
                                
********************************************

    )";

    const std::string imageLoadErrorMessage = R"(
***************************************
                                
  Could not open or find the image! 
                                
***************************************

    )";

    const std::string imageLoadSuccessMessage= R"(
 **************************************
                                 
     Image Loaded Successfully )
                                         
 **************************************
 )";

    const std::string boundaryMessageTemplate = R"(
********************************************************* 
                                    
 {BoundaryType} Center: (X:{x}, Y:{y}) Radius:({radius}). 
                                    
*********************************************************
)";
       
    void PrintImageResolution(int width, int height);
    void PrintImageLoadError();
    void PrintImageLoadSuccess();
    void PrintCircleCoordinates(const std::string& boundaryType,int x, int y, int radius);
    
}

#endif // MESSAGE_UTILS_H
