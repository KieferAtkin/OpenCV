#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void detectEyes(Mat frame, CascadeClassifier eye_cascade);

int main() {
    CascadeClassifier eye_cascade;

    if (!eye_cascade.load("Resources/haar-cascade-files/haarcascade_eye.xml")) {
        cerr << "Error loading Haar Cascade for eyes!" << endl;
        return -1;
    }

    Mat image = imread("Resources/WorkFaces.png");  // Replace "your_image.png" with your image path.

    if (image.empty()) {
        cerr << "Error loading the image!" << endl;
        return -1;
    }

    detectEyes(image, eye_cascade);

    imshow("Eye Detection", image);
    waitKey(0);

    return 0;
}

void detectEyes(Mat frame, CascadeClassifier eye_cascade) {
    vector<Rect> eyes;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect eyes
    eye_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Draw rectangles around detected eyes
    for (size_t i = 0; i < eyes.size(); i++) {
        Point eye_center(eyes[i].x + eyes[i].width / 2, eyes[i].y + eyes[i].height / 2);
        int radius = cvRound((eyes[i].width + eyes[i].height) * 0.25);
        circle(frame, eye_center, radius, Scalar(255, 255, 0), 2);
    }
}
