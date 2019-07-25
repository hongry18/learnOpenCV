#include <iostream>
#include "opencv2/opencv.hpp"

void onLevelChange(int p, void* data);

int main(void) {
    cv::Mat img = cv::Mat::zeros(400, 400, CV_8U);

    cv::namedWindow("img");
    cv::createTrackbar("level", "img", 0 ,16, onLevelChange, (void*)&img);

    cv::imshow("img", img);
    cv::waitKey();

    return 0;
}

void onLevelChange(int p, void* data) {
    cv::Mat img = *(cv::Mat*)data;

    img.setTo(p * 16);
    cv::imshow("img", img);
}
