#include <iostream>
#include "opencv2/opencv.hpp"

void onTrackbar(int p, void* d);

int main(void) {
    cv::Mat src = cv::imread("./sudoku.jpg", 0);
    if (!src.data) {
        return -1;
    }

    cv::namedWindow("dst");
    cv::createTrackbar("block size", "dst", 0, 200, onTrackbar, (void*)&src);
    cv::setTrackbarPos("block size", "dst", 11);

    cv::imshow("src", src);
    cv::imshow("dst", src);

    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}

void onTrackbar(int p, void* d) {
    cv::Mat  src = *(cv::Mat*)d;

    int bsize = p;
    if (bsize % 2 == 0) {
        bsize--;
    }

    if (bsize<3) {
        bsize = 3;
    }

    cv::Mat dst;
    cv::adaptiveThreshold(src, dst, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, bsize, 5);

    cv::imshow("dst", dst);
}
