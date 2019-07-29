#include <iostream>
#include "opencv2/opencv.hpp"

void erodeDilate();
void openClode();

int main(void) {
    erodeDilate();
    openClode();

    return 0;
}

void erodeDilate() {
    cv::Mat src = cv::imread("./milkdrop.bmp", 0);

    if (!src.data) {
        return;
    }

    cv::Mat bin;
    cv::threshold(src, bin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Mat d1, d2;
    cv::erode(bin, d1, cv::Mat());
    cv::dilate(bin, d2, cv::Mat());

    cv::imshow("src", src);
    cv::imshow("bin", bin);
    cv::imshow("d1", d1);
    cv::imshow("d2", d2);

    cv::waitKey();
    cv::destroyAllWindows();
}

void openClode() {
    cv::Mat src = cv::imread("./milkdrop.bmp", 0);

    if (!src.data) {
        return;
    }

    cv::Mat bin;
    cv::threshold(src, bin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Mat d1, d2;
    cv::morphologyEx(bin, d1, cv::MORPH_OPEN, cv::Mat());
    cv::morphologyEx(bin, d2, cv::MORPH_CLOSE, cv::Mat());

    cv::imshow("src", src);
    cv::imshow("bin", bin);
    cv::imshow("d1", d1);
    cv::imshow("d2", d2);

    cv::waitKey();
    cv::destroyAllWindows();
}
