#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;

int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, "{@input | Resources/EyeSignImages/TestImages2.bmp | input image}");
    Mat image = imread(samples::findFile(parser.get<String>("@input")));
    if (image.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }cout << "Image Loaded" << endl;

    Mat new_image = Mat::zeros(image.size(), image.type());

    double alpha = 1.0; // Simple contrast control 
    int beta = 0;       // Simple brightness control 
    int rType = -1;     /* desired output matrix type or, rather, the depth since the number of channels are the same as the
                           input has; if rtype is negative, the output matrix will have the same type as the input. */

    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";    cin >> beta;


    for (int pixelRowInImage = 0; pixelRowInImage < image.rows; pixelRowInImage++)
    {
        for (int pixelColumnsInImage = 0; pixelColumnsInImage < image.cols; pixelColumnsInImage++) 
        {
            for (int cycledBGRChannelFilter = 0; cycledBGRChannelFilter < image.channels(); cycledBGRChannelFilter++) 
            {
                new_image.at<Vec3b>(pixelRowInImage, pixelColumnsInImage)[cycledBGRChannelFilter] =
                    saturate_cast<uchar>(alpha * image.at<Vec3b>(pixelRowInImage, pixelColumnsInImage)[cycledBGRChannelFilter] + beta);
            }
        }
    }

    //image.convertTo(new_image, rType, alpha, beta);
    

    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();
    return 0;
}