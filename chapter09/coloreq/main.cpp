#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;

int main(void) {
    cv::Mat src = cv::imread("./pepper.bmp");
    if (!src.data) {
        printf("not load \n");
        return -1;
    }

    cv::Mat srcYcrcb;
    cv::cvtColor(src, srcYcrcb, cv::COLOR_BGR2YCrCb);

    vector<cv::Mat> planes;
    cv::split(srcYcrcb, planes);

    cv::equalizeHist(planes[0], planes[0]);

    cv::Mat dst, dstYcrcb;
    cv::merge(planes, dstYcrcb);

    cv::cvtColor(dstYcrcb, dst, cv::COLOR_YCrCb2BGR);

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();

    return 0;
}
