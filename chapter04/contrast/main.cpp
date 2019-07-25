#include <iostream>
#include "opencv2/opencv.hpp"

void contrast1();
void contrast2();

int main(void) {
    contrast1();
    contrast2();

    return 0;
}

void contrast1() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    float s = 2.f;
    cv::Mat dst = src * s;

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void contrast2() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    float alpha = 1.f;
    cv::Mat dst = src + (src - 128) * alpha;

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}
