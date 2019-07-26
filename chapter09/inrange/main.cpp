#include <iostream>
#include "opencv2/opencv.hpp"

int lHue = 40;
int uHue = 80;
cv::Mat src, srcHsv, mask;

void onHueChanged(int, void*);

int main(void) {
    src = cv::imread("candies.png", 1);
    if (!src.data) {
        return -1;
    }

    cv::cvtColor(src, srcHsv, cv::COLOR_BGR2HSV);
    cv::imshow("src", src);

    cv::namedWindow("mask");
    cv::createTrackbar("lower hue", "mask", &lHue, 179, onHueChanged);
    cv::createTrackbar("upper hue", "mask", &uHue, 179, onHueChanged);
    onHueChanged(0, 0);

    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}

void onHueChanged(int, void*) {
    cv::Scalar lb(lHue, 100, 0);
    cv::Scalar ub(uHue, 255, 255);
    cv::inRange(srcHsv, lb, ub, mask);

    cv::imshow("mask", mask);
}
