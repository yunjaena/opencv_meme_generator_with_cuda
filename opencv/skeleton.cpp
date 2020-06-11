#include <opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<omp.h>
#include<iostream>
#include"DS_definitions.h"
#include"DS_timer.h"

using namespace cv;
using namespace std;
// change skeleton to main
int skeleton()
{
	string fileName;
	Mat original_image;
	Mat serial_image;
	Mat parallel_image;
	uchar intensitiy;
	DS_timer timer(2);
	timer.setTimerName(0, (char*)"Serial");
	timer.setTimerName(1, (char*)"Parallel");

	cout << "이미지 파일명을 입력해주세요 : ";
	cin >> fileName;
	original_image = imread(fileName, IMREAD_COLOR);
	if (original_image.data == NULL) {
		cout << "이미지를 찾지 못했습니다.";
		getchar();
		getchar();
		return -1;
	}

	serial_image = Mat::zeros(original_image.size(), CV_8UC1);
	parallel_image = Mat::zeros(original_image.size(), CV_8UC1);

	/* image info */
	cout << "image info : " << "height : " << original_image.size().height << " width : " << original_image.size().width << endl;
	cout << "channel : " << original_image.channels() << endl;


	/* serial code*/
	timer.onTimer(0);
	

	timer.offTimer(0);

	/* parllel code*/
	timer.onTimer(1);


	timer.offTimer(1);


	bool isSame = true;
	for (int y = 0; y < original_image.rows; y++) {
		for (int x = 0; x < original_image.cols; x++) {
			if (parallel_image.at<uchar>(y, x) != serial_image.at<uchar>(y, x)) {
				isSame = false;
				break;
			}
		}
	}
	if (isSame)
		cout << "Same image with seial and parallel" << endl;
	else
		cout << "Different image with seial and parallel" << endl;

	timer.printTimer();

	/* save image */
	imwrite("parallel.jpg", parallel_image);

	/* show image */
	namedWindow("original", WINDOW_NORMAL);
	imshow("original", original_image);
	namedWindow("serial", WINDOW_NORMAL);
	imshow("serial", serial_image);
	namedWindow("parallel", WINDOW_NORMAL);
	imshow("parallel", parallel_image);
	waitKey();
	destroyAllWindows();
}
