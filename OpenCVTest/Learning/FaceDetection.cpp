#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images - Basic Functions  //////////////////////

void main() {

	string path = "Resources/WorkFaces.png";
	Mat imgSource = imread(path);
	
	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haar-cascade-files/haarcascade_frontalface_default.xml");

	if( faceCascade.empty() ) { cout << "XML file not found"<< endl; }

	vector<Rect> faces;
	faceCascade.detectMultiScale(imgSource, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(imgSource, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

	imshow("Image", imgSource);

	waitKey(0);

}