#include <iostream>
#include "opencv2/opencv.hpp"

void sobelDerivative();
void sobelEdge();
void cannyEdge();

int main(void) {
    sobelDerivative();
    sobelEdge();
    cannyEdge();

    return 0;
}

void sobelDerivative() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    cv::Mat mx = cv::Mat_<float>({1,3}, {-1/2.f, 0, 1/2.f});
    cv::Mat my = cv::Mat_<float>({1,3}, {-1/2.f, 0, 1/2.f});

    cv::Mat dx, dy;
    cv::filter2D(src, dx, -1, mx, cv::Point(-1, -1), 128);
    cv::filter2D(src, dy, -1, my, cv::Point(-1, -1), 128);

    cv::imshow("src", src);
    cv::imshow("dx", dx);
    cv::imshow("dy", dy);

    cv::waitKey();
    cv::destroyAllWindows();
}

void sobelEdge() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    cv::Mat dx, dy;
    cv::Sobel(src, dx, CV_32F, 1, 0);
    cv::Sobel(src, dy, CV_32F, 0, 1);

    cv::Mat fmag, mag;
    cv::magnitude(dx, dy, fmag);
    fmag.convertTo(mag, CV_8U);

    cv::Mat edge = mag > 150;

    cv::imshow("src", src);
    cv::imshow("mag", mag);
    cv::imshow("edge", edge);

    cv::waitKey();
    cv::destroyAllWindows();
}

void cannyEdge() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    cv::Mat d1, d2;
    cv::Canny(src, d1, 50, 100);
    cv::Canny(src, d2, 50, 100);

    cv::imshow("src", src);
    cv::imshow("d1", d1);
    cv::imshow("d2", d2);

    cv::waitKey();
    cv::destroyAllWindows();
}
