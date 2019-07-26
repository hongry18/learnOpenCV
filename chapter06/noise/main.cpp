#include <iostream>
#include "opencv2/opencv.hpp"

void noiseGaussian();
void filterBilateral();
void filterMedian();

int main(void) {
    noiseGaussian();
    filterBilateral();
    filterMedian();

    return 0;
}

void noiseGaussian() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    cv::imshow("src", src);

    for (int stddev = 10; stddev < 31; stddev += 10) {
        cv::Mat noise(src.size(), CV_32S);
        cv::randn(noise, 0, stddev);

        cv::Mat dst;
        cv::add(src, noise, dst, cv::Mat(), CV_8U);

        std::string desc = cv::format("stddev = %d", stddev);
        cv::putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);
        cv::imshow("dst", dst);
        cv::waitKey();
    }

    cv::destroyAllWindows();
}

void filterBilateral() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    cv::imshow("src", src);

    cv::Mat noise(src.size(), CV_32S);
    cv::randn(noise, 0, 5);
    cv::add(src, noise, src, cv::Mat(), CV_8U);

    cv::Mat dst1, dst2;
    cv::GaussianBlur(src, dst1, cv::Size(), 5);
    cv::bilateralFilter(src, dst2, -1, 10, 5);

    cv::imshow("dst1", dst1);
    cv::imshow("dst2", dst2);

    cv::waitKey();
    cv::destroyAllWindows();
}

void filterMedian() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    cv::imshow("src", src);

    int num = (int)(src.total() * 0.1);
    for (int i=0; i<num; i++) {
        int x = rand() % src.cols;
        int y = rand() % src.rows;
        src.at<uchar>(y,x) = (i%2)*255;
    }

    cv::Mat d1, d2;
    cv::GaussianBlur(src, d1, cv::Size(), 1);
    cv::medianBlur(src, d2, 3);

    cv::imshow("dst1", d1);
    cv::imshow("dst2", d2);

    cv::waitKey();
    cv::destroyAllWindows();

}
