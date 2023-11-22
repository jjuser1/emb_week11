#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/photo.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    VideoCapture cap;
    cap.open("/dev/video0", CAP_V4L2);
    
    if (!cap.isOpened()) {
        cerr << "Error: Can't open camera" << endl;
        return -1;
    }

    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
    
    if (!video.isOpened()) {
        cerr << "Error: Can't open video writer" << endl;
        return -1;
    }

    cout << "Camera opened successfully" << endl;

    Mat img;
    int count = 0;
    int max = (argc > 1) ? stoi(argv[1]) : 50;

    while (count <= max) {
        if (!cap.read(img)) {
            cerr << "Error: Can't read image from camera" << endl;
            break;
        }

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        Mat sobelX, sobelY, sobel;
        Sobel(gray, sobelX, CV_8U, 1, 0);
        Sobel(gray, sobelY, CV_8U, 0, 1);
        sobel = abs(sobelX) + abs(sobelY);

        video.write(sobel);
        count++;
    }

    cap.release();
    video.release();
    return 0;
}

