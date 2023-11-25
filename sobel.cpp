#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp> // OpenCV 라이브러리
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/photo.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	// 이미지의 높이, 너비 및 픽셀 값을 저장하기 위한 변수들
	int height, width;
	int n_height, n_width;
	float R_val, G_val, B_val;
	float average_gray;

	// 비디오 캡처 객체 생성 및 카메라 열기
	VideoCapture cap;
	cap.open("/dev/video0", CAP_V4L2); // V4L2 카메라 열기
	
	if (!cap.isOpened()) {
		printf("Can't open Camera\n");
		return -1;
	}

	// 프레임의 기본 해상도 가져오기
	int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	// 비디오 라이터 객체 생성 및 비디오 저장
	VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

	printf("Open Camera\n");
	Mat img;
	int count = 0; int max;

	// 사용자가 명령줄 인수로 최대 프레임 수를 입력하면 해당 수만큼 캡처
	if (argc > 1) {
		max = int(argv[1]);
	}
	else {
		max = 50; // 기본적으로 50프레임까지만 캡처
	}

	// 최대 수의 프레임까지 비디오에서 프레임을 읽고 처리
	while (count <= max) {
		cap.read(img); // 프레임 읽기

		if (img.empty()) break; // 프레임이 비어있으면 종료

		if (img.empty()) {
			printf("image load error\n");
			return -1;
		}

		// 이미지의 높이와 너비 가져오기
		height = img.rows;
		width = img.cols;

		// 이미지를 그레이스케일로 변환
		Mat gray(height, width, CV_8UC1);
		cvtColor(img, gray, COLOR_BGR2GRAY);

		// Sobel 필터 적용하여 엣지 감지
		Mat sobelX, sobelY, sobel;
		Sobel(gray, sobelX, CV_8U, 1, 0);
		Sobel(gray, sobelY, CV_8U, 0, 1);
		sobel = abs(sobelX) + abs(sobelY);

		// 그레이스케일 이미지를 다시 BGR 이미지로 변환하여 색상 이미지로 만듦
		Mat sobel_color;
		cvtColor(sobel, sobel_color, COLOR_GRAY2BGR);

		// 비디오 라이터로 변환된 이미지 프레임 저장
		video.write(sobel_color);

		count++;
	}

	// 사용한 자원 해제
	cap.release();
	video.release();
	return 0;
}
