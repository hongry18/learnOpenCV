#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;

void contoursBasic();
void contoursHier();

int main(void) {
    contoursBasic();
    contoursHier();

    return 0;
}

void contoursBasic() {
    cv::Mat src = cv::imread("./contours.bmp", 0);
    if (!src.data) {
        return;
    }

    vector<vector<cv::Point>> contours;
    cv::findContours(src, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);

    for (int i=0; i<contours.size(); i++) {
        cv::Scalar c(rand() & 255, rand() & 255, rand() & 255);
        cv::drawContours(dst, contours, i, c, 2);
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void contoursHier() {
    cv::Mat src = cv::imread("./contours.bmp", 0);
    if (!src.data) {
        return;
    }

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours(src, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);

    for (int i=0; i>=0; i=hierarchy[i][0]) {
        cv::Scalar c(rand() & 255, rand() & 255, rand() & 255);
        cv::drawContours(dst, contours, i, c, -1, cv::LINE_8, hierarchy);
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}
