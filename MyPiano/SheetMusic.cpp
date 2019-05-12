#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
	Mat image = Mat(Size(300, 400), CV_8UC1, Scalar(255));
	image(Rect(0, 0, 300, 200)) = Scalar(1);

	putText(image, "Hello", Point(50, 100), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255));
	putText(image, "World", Point(150, 300), FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 0));

	cout << "Hello World!" << endl;
	imshow("image", image);

	waitKey();
	return 0;
}