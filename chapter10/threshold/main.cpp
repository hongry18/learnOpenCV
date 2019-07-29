#include <iostream>
#include "opencv2/opencv.hpp"

void onThreshold(int p, void* d);

int main(int argc, char** argv) {
    cv::Mat src;

    if (argc < 2) {
        src = cv::imread("./neutrophils.png", 0);
    } else {
        src = cv::imread(argv[1], 0);
    }

    if (!src.data) {
        return -1;
    }

    cv::imshow("src", src);
    cv::imshow("dst", src);

    cv::namedWindow("dst");
    cv::createTrackbar("threshold", "dst", 0, 255, onThreshold, (void*)&src);
    cv::setTrackbarPos("threshold", "dst", 128);

    cv::waitKey();

    return 0;
}

void onThreshold(int p, void* d) {
    cv::Mat src = *(cv::Mat*)d;

    cv::Mat dst;
    cv::threshold(src, dst, p, 255, cv::THRESH_BINARY);
    cv::imshow("dst", dst);
}
