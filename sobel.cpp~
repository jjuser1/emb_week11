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

	int height, width;
	int n_height, n_width;
	float R_val, G_val, B_val;
	float average_gray;

	VideoCapture cap;
	cap.open("/dev/video0", CAP_V4L2);
	
	if (!cap.isOpened()) {
		printf("Can't open Camera\n");
		return -1;
	}


	// Default resolutions of the frame are obtained. The default resolutions are system dependent.
	int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);


	// Define the codec and create VideoWriter object. The output is stored in 'outcpp.avi' file.
	VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

	printf("Open Camera\n");
	Mat img, img1;
	int count = 0; int max;

	if (argc > 1) {
		max = int(argv[1]);
	}
	else {
		max = 50;
	}

	while (count <= max) {
		cap.read(img);
		if (img.empty()) break;
		
		if (argc > 1) {
			img1 = imread(argv[1], IMREAD_COLOR);
		}
		else {
			img1 = imread(img, IMREAD_COLOR);
		}

		if (img1.empty()) {
			printf("image load error\n");
			return -1;
		}

		height = img1.rows;
		width = img1.cols;
		Mat gray(height, width, CV_8UC1);
		cvtColor(img1, gray, COLOR_BGR2GRAY);

		Mat sobelX,sobelY,sobel;

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
