#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;



void main()
{
    //string imagePath = "Resources/EyeSignImages/Smarties.jpg";
    string imagePath = "Resources/EyeSignImages/testImages1.bmp";
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
    
    HoughCircles(imageDilated, circles, HOUGH_GRADIENT, 1,
        imageDilated.rows / 16,  // change this value to detect circles with different distances to each other
        100, 30, 1, 30 // change the last two parameters
        // (min_radius & max_radius) to detect larger circles
    );

    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle(imageSource, center, 1, Scalar(100, 0, 200), 2, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(imageSource, center, radius, Scalar(0, 234, 255),2, LINE_AA); 
    }

    imshow("detected circles", imageSource);
    imshow("image Gray", imageGray);
    imshow("image median blur", imageMedianBlur);
    imshow("image Canny", imageCanny);
    imshow("image Dilated", imageDilated);

    waitKey(0);

}