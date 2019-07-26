#include <iostream>
#include "opencv2/opencv.hpp"

void blurringMean();
void blurringGaussian();

int main(void) {

    blurringMean();
    blurringGaussian();

    return 0;
}

void blurringMean() {
    cv::Mat src = cv::imread("rose.bmp", 0);

    if (!src.data) {
        return;
    }

    cv::imshow("src", src);

    cv::Mat dst;
    for (int ksize = 3; ksize < 8; ksize += 2) {
        cv::blur(src, dst, cv::Size(ksize, ksize));

        std::string desc = cv::format("Mean: %d x %d", ksize, ksize);
        cv::putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);

        cv::imshow("dst", dst);
        cv::waitKey();
    }

    cv::destroyAllWindows();
}

void blurringGaussian() {
    cv::Mat src = cv::imread("rose.bmp", 0);

    if (!src.data) {
        return;
    }

    cv::imshow("src", src);

    cv::Mat dst;
    for (int sigma = 1; sigma < 6; sigma++) {
        cv::GaussianBlur(src, dst, cv::Size(0, 0), (double)sigma);

        std::string desc = cv::format("Gaussian Sigma: %d", sigma);
        cv::putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);

        cv::imshow("dst", dst);
        cv::waitKey();
    }

    cv::destroyAllWindows();
}
