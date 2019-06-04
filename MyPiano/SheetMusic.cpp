#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <fstream>

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


	//선 사이 평균 간격 구하기
	bool first_interval = true;
	int first_interval_loc = 0; //첫 번째 간격
	int sum_line_interval = 0; //간격 합(평균을 구하기 위함)

	for (int i = 2; i < lineNum; i++) {
		int tmp_interval = line[i] - line[i - 1]; //선 사이 간격 계산

		if (tmp_interval != 1) { //간격이 1이 아니면
			if (first_interval == true) {
				first_interval_loc = tmp_interval;
				first_interval = false;
			}

			if (first_interval == false && tmp_interval > first_interval_loc * 2) {
				break; //다음 묶음의 오선이면 break
			}

			sum_line_interval += tmp_interval;
		}
	}
	int avg_interval = sum_line_interval / 4;
	cout << "평균 간격 : " << avg_interval << endl;



	//오선 출력
	Mat line_img = Mat(input_img.rows, input_img.cols, CV_8UC1);
	int line_count = 0;
	for (int y = 0; y < input_img.rows; y++) {
		uchar* pointer_binary = img_binary.ptr<uchar>(y);
		uchar* pointer_line = line_img.ptr<uchar>(y);
		if (line_count < lineNum && y == line[line_count]) {
			line_count++;
			for (int x = 0; x < input_img.cols; x++) {
				pointer_line[x] = pointer_binary[x];
			}
			cout << y << endl;
		}
		else {
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
	}


	//오선 제거
	Mat img_new = Mat(input_img.rows, input_img.cols, CV_8UC1);
	int lineTmp = 0;
	int interval_count_tmp = 0;
	int f_tmp = 0;
	for (int y = 0; y < input_img.rows; y++) {
		uchar* pointer_line = img_new.ptr<uchar>(y);
		uchar* pointer_binary = img_binary.ptr<uchar>(y);
		f_tmp = interval_count_tmp % 5;


		if (f_tmp==1 && line[lineTmp-1] + avg_interval+avg_interval/2 < y && y < line[lineTmp]- avg_interval+ avg_interval/2) {
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
			interval_count_tmp++;
			if (line[lineTmp] - line[lineTmp - 1] == 1) {
				interval_count_tmp--;
			}
		}
		else {
			for (int x = 0; x < input_img.cols; x++) {
				pointer_line[x] = pointer_binary[x];
			}
		}
	}


	//노이즈 제거
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
	erode(img_new, img_new, mask); //학교종
	


	Mat dstImage;
	Mat edge;
	Canny(img_new, edge, 50, 150); //edge 검출
	bitwise_not(edge, edge); //반전

	//edge 강조
	vector<vector<Point>> contours;
	findContours(edge.clone(), contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
	drawContours(edge, contours, -1, Scalar(0, 0, 0), 1);
	cvtColor(edge, dstImage, COLOR_GRAY2BGR);

	Mat labels, stats, centroids;
	int nlabels = connectedComponentsWithStats(edge, labels, stats, centroids, 8, CV_32S);
	Point point_arr[999]; //추출한 음 좌표
	string point_string[999]; //추출한 음
	//int Point_position[999];
	for (int i = 2; i < nlabels; i++) {
		int area = stats.at<int>(i, CC_STAT_AREA);
		int center_x = centroids.at<double>(i, 0);
		int center_y = centroids.at<double>(i, 1);
		int left = stats.at<int>(i, CC_STAT_LEFT);
		int top = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);

		rectangle(dstImage, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1);
		putText(dstImage, to_string(i), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
		
		//cout << "음 추출 : " << i << " - (" << center_x << ", " << center_y << ")";
		point_arr[i] = Point(center_x, center_y);
	}



	Point final_point_arr[999]; //음 좌표
	final_point_arr[0].x = 0;
	int temp_point_x = final_point_arr[0].x;
	string final_point_string[999]; //음
	int prv_temp_x = 0;
	int temp_x = 5;
	int temp_y = 5;
	Point x_min;
	x_min.x = input_img.cols;
	int interval_position[99];
	int interval_position_count = 0;
	for (int x = 2; x < nlabels; x++) {
		if (point_arr[x].y > line[temp_x]+4 + avg_interval * 2) {
			temp_x += 5;
			temp_y += 5;
			prv_temp_x += 5;
			temp_point_x = 0;
			interval_position[interval_position_count] = x - 1;
			interval_position_count++;
		}
		
		x_min.x = input_img.cols;
		for (int y = 2; y < nlabels; y++) {
			if (temp_point_x < point_arr[y].x && point_arr[y].x < x_min.x && line[prv_temp_x] + 4 + avg_interval * 2 < point_arr[y].y && point_arr[y].y <= line[temp_x] + 4 + avg_interval * 2) {
				x_min = point_arr[y];
			}
			else if (point_arr[y].y > line[temp_y] + 4 + avg_interval * 2) {
				
				break;
			}
		}
		final_point_arr[x] = x_min;
		temp_point_x = final_point_arr[x].x;
		cout << "(" << final_point_arr[x].x << ", " << final_point_arr[x].y << ")";



		for (int l = 1; l < lineNum; l++) {
			if (final_point_arr[x].y == line[l] + 4 || final_point_arr[x].y == line[l] + 5 || final_point_arr[x].y == line[l] + 3) {
				switch (l % 5) {
				case 1: cout << "파"; point_string[x] = "'"; break;
				case 2: cout << "레"; point_string[x] = "l"; break;
				case 3: cout << "시"; point_string[x] = "j"; break;
				case 4: cout << "솔"; point_string[x] = "g"; break;
				case 0: cout << "미"; point_string[x] = "d"; break;
				}
			}
			else if (final_point_arr[x].y == line[l] + avg_interval / 2 + 4 || final_point_arr[x].y == line[l] + avg_interval / 2 + 5 || final_point_arr[x].y == line[l] + avg_interval / 2 + 3) {
				switch (l % 5) {
				case 1: cout << "미"; point_string[x] = ";"; break;
				case 2: cout << "도"; point_string[x] = "k"; break;
				case 3: cout << "라"; point_string[x] = "h"; break;
				case 4: cout << "파"; point_string[x] = "f"; break;
				case 0: cout << "레"; point_string[x] = "s"; break;
				}
			}
			else if (final_point_arr[x].y == line[l] +avg_interval + 4 || final_point_arr[x].y == line[l] + avg_interval + 5 || final_point_arr[x].y == line[l] + avg_interval + 3) {
				if (l % 5 == 0) {
					cout << "도"; point_string[x] = "a";
				}
			}
		}
		cout << endl;
	}

	ofstream out("1.txt");
	out << nlabels - 1 - 2 << endl;
	for (int x = 2; x < nlabels-1; x++) {
		out << point_string[x] << "250" << endl;
	}
	out << endl << "0";
	out.close();

	ofstream out2("2.txt");
	interval_position_count = 0;
	out2 << nlabels - 1 - 2 << endl;
	for (int x = 2; x < nlabels - 1; x++) {
		out2 << point_string[x] << "250" << endl;
		if (x == interval_position[interval_position_count]) {
			out2 << endl;
			interval_position_count++;
		}
	}
	out2 << endl << "0";
	
	out2.close();



	cv::imshow("binary", img_binary);
	cv::imshow("line", line_img);
	cv::imshow("new", img_new);
	cv::imshow("reeeesullllt", dstImage);

	cv::waitKey(0);
	return 0;

}