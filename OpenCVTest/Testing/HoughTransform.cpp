#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#include "datetime_utils.h"

using namespace cv;
using namespace std;

/********** back up hough ********/
//int inverseRatio = 1;
//int hough_Min_Threshold = 33;
//int hough_Max_Threshold = 180;
//int hough_Min_Distance = 16;
//int hough_min_Radius = 50;
//int hough_max_Radius = 150;



/* pupil boundry */
double pupil_inverseRatio = 1.0;
double pupil_param_1 = 30; // to do with Canny.
double pupil_param_2 = 50; // accuracy : lower is less good
double pupil_min_dist_div = 16; // For some reason the lower the number the better the result. Could result in false.
int pupil_min_radius = 55;
int pupil_max_radius = 165;

/* iris boundry */
double iris_inverseRatio = 1.0;
double param_1 = 30; // to do with Canny.
double param_2 = 50; // accuracy : lower is less good
double iris_min_dist_div = 16; // For some reason the lower the number the better the result. Could result in false.
int min_radius = 55;
int max_radius = 180;

int canny_LowThreshold = 0;
const int canny_Max_lowThreshold = 100;
const int cannyRatio = 3;
const int canny_Kernel_Size = 3;



static void LoadImageFromPath(Mat& imageSource)
{
    //string imagePath = "Resources/EyeSignImages/Smarties.jpg";
    //string imagePath = "Resources/EyeSignImages/Name6.bmp";
    string imagePath = "Resources/EyeSignImages/TestImages2.bmp";


    // Loads image and converts.
    imageSource = imread(imagePath, IMREAD_COLOR);
    if (imageSource.empty())
    {
        std::cout << "*********************************** " << endl;
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "*********************************** " << endl;
    }
    else
    {
        std::cout << "*********************************** " << endl;
        std::cout << "Image Loaded" << std::endl;
        std::cout << "*********************************** " << endl;
    }

    getGMTDateTime();
}

int main()
{
    Mat imageGray, imageMedianBlur, imageCanny, imageDilated;
        
    cv::Mat imageLoaded;
    LoadImageFromPath(imageLoaded);

    cv::Mat imageSource = imageLoaded;
    

    cvtColor(imageSource, imageGray, COLOR_BGR2GRAY);
    medianBlur(imageGray, imageMedianBlur, 5);
    Canny(imageMedianBlur, imageCanny, 25, 75);
   

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imageCanny, imageDilated, kernel);


    /*
     * C:(xcenter,ycenter,r)
    */

    // Define a vector to store the detected circles
    vector<Vec3f> detectedCircles;

    // Detect circles using the Hough transform
    HoughCircles(imageDilated,
                 detectedCircles,
                 HOUGH_GRADIENT,
                 pupil_inverseRatio,
                 imageDilated.rows / pupil_min_dist_div,
                 pupil_param_1,
                 pupil_param_2,
                 pupil_min_radius,
                 pupil_max_radius);

    // Iterate over each detected circle
    for (size_t circleIndex = 0; circleIndex < detectedCircles.size(); circleIndex++)
    {
        // Extract the circle parameters: center coordinates and radius
        Vec3i circleParams = detectedCircles[circleIndex];
        Point center = Point(circleParams[0], circleParams[1]); // [0] = Xcenter, [1] = Ycenter
        

        // Draw a small circle at the center of the current circle
        // using a yellow color (BGR: 0, 255, 255) with a thickness of 2 pixels
        circle(imageSource, center, 1, Scalar(0, 255, 255), 2, LINE_AA);

        // Extract the radius of the current circle
        int radius = circleParams[2]; // [2] = the radius.
        

        // Draw the outline of the current circle
        // using the center, radius, yellow color (BGR: 0, 255, 255), and a thickness of 2 pixels
        circle(imageSource, center, radius, Scalar(0, 255, 255), 2, LINE_AA);

        std::cout << "*********************************** " << endl;
        std::cout << " Center: (" << center.x << ", " << center.y << ")" << " " << "Radius: (" << radius << "). " << std::endl;
        std::cout << "*********************************** " << endl;
    }


    vector<Vec3f> circles2;
    HoughCircles(imageDilated,                    // Input
        circles2,                                 // Output
        HOUGH_GRADIENT,                           // Detection method
        iris_inverseRatio,                        // Inverse ratio of the accumulator resolution to the image resolution. 
        imageDilated.rows / iris_min_dist_div,    // change this value to detect circles with different distances to each other
        param_1,
        param_2,
        min_radius,
        max_radius
    );

    for (size_t i = 0; i < circles2.size(); i++)
    {
        Vec3i c = circles2[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(imageSource, center, 1, Scalar(0, 255, 255), 2, LINE_AA);
        // circle outline
        int radius = c[2];

        // circle(imageSource, center, radius, Scalar(0, 255, 255), 2, LINE_AA);
        circle(imageSource, center, radius, Scalar(255, 0, 255), 2, LINE_AA);

        std::cout << "*********************************** " << endl;
        std::cout << " Limbic Center: (" << center.x << ", " << center.y << ")" << " " << "Radius: (" << radius << "). " << std::endl;
        std::cout << "*********************************** " << endl;
    }
    

    imshow("detected circles", imageSource);
    imshow("image Canny", imageCanny);
 

    waitKey(0);

    return 0;

}