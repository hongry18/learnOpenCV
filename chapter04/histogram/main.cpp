#include <iostream>
#include "opencv2/opencv.hpp"

cv::Mat calcGrayHist(const cv::Mat& img);
cv::Mat getGrayHistImage(const cv::Mat& hist);

void histogramStretching();
void histogramEqualization();

int main(void) {
    histogramStretching();
    histogramEqualization();

    return 0;
}

cv::Mat calcGrayHist(const cv::Mat& img) {
    CV_Assert(img.type() == CV_8UC1);

    cv::Mat hist;
    int channels[] = {0};
    int dims = 1;
    const int histSize[] = {256};
    float graylevel[] = {0, 256};
    const float *ranges[] = { graylevel };

    cv::calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges);

    return hist;
}

cv::Mat getGrayHistImage(const cv::Mat& hist) {
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.size() == cv::Size(1, 256));

    int limit = 256;
    double histMax;
    cv::minMaxLoc(hist, 0, &histMax);

    cv::Mat imgHist(100, limit, CV_8UC1, cv::Scalar(255));
    for (int i=0; i<limit; i++) {
        cv::line(imgHist, cv::Point(i, 100), cv::Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), cv::Scalar(0));
    }

    return imgHist;
}

void histogramStretching() {
    cv::Mat src = cv::imread("./hawkes.bmp", 0);

    if (!src.data) {
        return;
    }

    double gmin, gmax;
    cv::minMaxLoc(src, &gmin, &gmax);
    cv::Mat dst = (src - gmin) * 255 / (gmax - gmin);

    cv::imshow("src", src);
    cv::imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

    cv::imshow("dst", dst);
    cv::imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

    cv::waitKey();
    cv::destroyAllWindows();
}

void histogramEqualization() {
    cv::Mat src = cv::imread("./hawkes.bmp", 0);

    if (!src.data) {
        return;
    }

    cv::Mat dst;
    cv::equalizeHist(src, dst);

    cv::imshow("src", src);
    cv::imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

    cv::imshow("dst", dst);
    cv::imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

    cv::waitKey();
    cv::destroyAllWindows();
}
