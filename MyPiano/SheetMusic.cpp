#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat GS_threshold(Mat src_image, double thresh, int threshold_type) {
	double max_value = 255.0;
	if (threshold_type == cv::THRESH_BINARY || threshold_type == cv::THRESH_BINARY_INV)
		max_value = thresh;
	cv::Mat dst_image = cv::Mat(src_image.size(), src_image.type());
	cv::threshold(src_image, dst_image, thresh, max_value, threshold_type);
	return dst_image;
}

int main() {
	Mat input_img = imread("비행기.png"); //원본 영상

	//그레이스케일 영상
	Mat img_gray = Mat(input_img.rows, input_img.cols, CV_8UC1); 
	for (int y = 0; y < input_img.rows; y++) {
		for (int x = 0; x < input_img.cols; x++) {
			uchar blue = input_img.at<Vec3b>(y, x)[0];
			uchar green = input_img.at<Vec3b>(y, x)[1];
			uchar red = input_img.at<Vec3b>(y, x)[2];
			uchar gray = (blue + green + red) / 3.0; 
			img_gray.at<uchar>(y, x) = gray;
		}
	}

	//이진 영상
	Mat img_binary = Mat(input_img.rows, input_img.cols, CV_8UC1);
	threshold(img_gray, img_binary, 127, 255, THRESH_OTSU);

	int limit = (int)((input_img.cols / 100.0) * 80);
	int line[99999];
	int lineNum = 0;
	line[lineNum] = 0;
	lineNum++;
	
	//오선 위치 추출
	for (int y = 0; y < input_img.rows; y++) {
		uchar* pointer_input = img_binary.ptr<uchar>(y);
		
		int cnt = 0;

		for (int x = 0; x < input_img.cols; x++) {
			int temp = pointer_input[x];
			if (temp == 0) cnt++; //한 가로 줄에서 값이 255인 픽셀 개수 세기
		}

		if (cnt >= limit) { //오선 위치 추가
			line[lineNum] = y;
			lineNum++;
		}
	}
	line[lineNum] = input_img.rows - 1;

	int interval_line = line[2] - line[1]; //선 간격

	//오선 제거
	Mat img_new = Mat(input_img.rows, input_img.cols, CV_8UC1);
	int lineTmp = 0;
	int f_tmp = 0;
	for (int y = 0; y < input_img.rows; y++) {
		uchar* pointer_line = img_new.ptr<uchar>(y);
		uchar* pointer_binary = img_binary.ptr<uchar>(y);
		f_tmp = lineTmp % 5;
		if (f_tmp==1 && line[lineTmp-1] + interval_line+3 < y && y < line[lineTmp]- interval_line+3) {
			for (int x = 0; x < input_img.cols; x++) {
				switch (pointer_binary[x]) {
				case 0:
					pointer_line[x] = 255 + pointer_binary[x];
					break;
				case 255:
					pointer_line[x] = pointer_binary[x];
					break;
				}
			}
		}
		else if (y == line[lineTmp]) {
			for (int x = 0; x < input_img.cols; x++) {
				pointer_line[x] = 255 + pointer_binary[x];
			}
			lineTmp++;
		}
		else {
			for (int x = 0; x < input_img.cols; x++) {
				pointer_line[x] = pointer_binary[x];
			}
		}
	}

	Mat mask = getStructuringElement(CV_SHAPE_RECT, Size(2, 2));
	erode(img_new, img_new, mask);
	dilate(img_new, img_new, mask);
	dilate(img_new, img_new, mask);
	dilate(img_new, img_new, mask);
	dilate(img_new, img_new, mask);
	dilate(img_new, img_new, mask);
	erode(img_new, img_new, mask);
	erode(img_new, img_new, mask);
	erode(img_new, img_new, mask);
	erode(img_new, img_new, mask);
	

	imshow("result", img_binary);
	imshow("new", img_new);
	waitKey(0);
	return 0;

}