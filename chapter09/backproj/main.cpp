#include <iostream>
#include "opencv2/opencv.hpp"

int main(void) {
    cv::Mat ref, refYcrcb, mask;

    ref = cv::imread("ref.png", 1);
    mask = cv::imread("mask.bmp", 0);
    cv::cvtColor(ref, refYcrcb, cv::COLOR_BGR2YCrCb);

    cv::Mat hist;
    int channels[] = {1,2};
    int crBins = 128;
    int cbBins = 128;
    int histSize[] = { crBins, cbBins };
    float crRange[] = {0,256};
    float cbRange[] = {0,256};
    const float* ranges[] = {crRange, cbRange};

    cv::calcHist(&refYcrcb, 1, channels, mask, hist, 2, histSize, ranges);

    cv::Mat src, srcYcrcb;
    src = cv::imread("kids.png", 1);
    cv::cvtColor(src, srcYcrcb, cv::COLOR_BGR2YCrCb);

    cv::Mat backproj;
    cv::calcBackProject(&srcYcrcb, 1, channels, hist, backproj, ranges, 1, true);

    cv::imshow("src", src);
    cv::imshow("backproj", backproj);
    cv::waitKey();

    return 0;
}
