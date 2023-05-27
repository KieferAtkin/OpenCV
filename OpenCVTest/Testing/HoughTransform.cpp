#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

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

void main()
{
    //string imagePath = "Resources/EyeSignImages/Smarties.jpg";
    //string imagePath = "Resources/EyeSignImages/Name6.bmp";
    string imagePath = "Resources/EyeSignImages/TestImages2.bmp";

    // Loads an image
    Mat imageSource = imread(imagePath, IMREAD_COLOR);

    // Check if image is loaded fine
    if (imageSource.empty()) {
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", imagePath);
       }

    Mat imageGray, imageMedianBlur, imageCanny, imageDilated;

    cvtColor(imageSource, imageGray, COLOR_BGR2GRAY);
    medianBlur(imageGray, imageMedianBlur, 5);
    Canny(imageMedianBlur, imageCanny, 25, 75);
   

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imageCanny, imageDilated, kernel);

    vector<Vec3f> circles;    
    HoughCircles(imageDilated,                   // Input
        circles,                                 // Output
        HOUGH_GRADIENT,                          // Detection method
        pupil_inverseRatio,                            // Inverse ratio of the accumulator resolution to the image resolution. 
        imageDilated.rows / pupil_min_dist_div,  // change this value to detect circles with different distances to each other
        pupil_param_1,
        pupil_param_2,
        pupil_min_radius,  
        pupil_max_radius
    );

    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(imageSource, center, 1, Scalar(0, 255, 255), 2, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(imageSource, center, radius, Scalar(0, 255, 255),2, LINE_AA);
    }

    vector<Vec3f> circles2;
    HoughCircles(imageDilated,                   // Input
        circles2,                                 // Output
        HOUGH_GRADIENT,                          // Detection method
        iris_inverseRatio,                            // Inverse ratio of the accumulator resolution to the image resolution. 
        imageDilated.rows / iris_min_dist_div,  // change this value to detect circles with different distances to each other
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
        circle(imageSource, center, radius, Scalar(0, 255, 255), 2, LINE_AA);
    }
    

    imshow("detected circles", imageSource);
    imshow("image Canny", imageCanny);
 

    waitKey(0);

}