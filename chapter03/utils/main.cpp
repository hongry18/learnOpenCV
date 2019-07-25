#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

void maskSet2();
void maskCopy2();
void timeInverse();
void usefulFnc();

int main(void) {

    maskSet2();
    maskCopy2();
    timeInverse();
    usefulFnc();

    return 0;
}

void maskSet2() {
    cv::Mat src = cv::imread("./lenna.bmp", 1);
    cv::Mat mask = cv::imread("./mask_smile.bmp", 0);

    if (!src.data || !mask.data) {
        return;
    }

    src.setTo(cv::Scalar(0, 255, 255), mask);
    cv::imshow("src", src);
    cv::imshow("mask", mask);

    cv::waitKey();
    cv::destroyAllWindows();
}

void maskCopy2() {
    cv::Mat src = cv::imread("airplane.bmp", 1);
    cv::Mat mask = cv::imread("mask_plane.bmp", 0);
    cv::Mat dst = cv::imread("field.bmp", 1);
    
    if (!src.data || !mask.data || !dst.data) {
        return;
    }

    src.copyTo(dst, mask);

    cv::imshow("src", src);
    cv::imshow("mask", mask);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void timeInverse() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if(!src.data) {
        return;
    }
    cv::Mat dst(src.size(), src.type());
    cv::TickMeter tm;
    tm.start();

    for (int i=0; i<src.rows; i++) {
        for (int j=0; j<src.cols; j++) {
            dst.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);
        }
    }

    tm.stop();

    cout << "image inverse took " << tm.getTimeMilli() << "ms" << endl;
}

void usefulFnc() {
    cv::Mat src = cv::imread("./lenna.bmp", 0);
    if (!src.data) {
        return;
    }

    cout << "sum: " << (int)sum(src)[0] << endl;
    cout << "mean: " << (int)mean(src)[0] << endl;

    double minVal, maxVal;
    cv::Point minP, maxP;

    cv::minMaxLoc(src, &minVal, &maxVal, &minP, &maxP);
    cout << "minVal: " << minVal << ", at " << minP << endl;
    cout << "maxVal: " << maxVal << ", at " << maxP << endl;

    cv::Mat src2 = cv::Mat_<float>({1,5}, {-1.f, -0.5f, 0.f, 0.5f, 1.f});

    cv::Mat dst;
    cv::normalize(src2, dst, 0, 255, cv::NORM_MINMAX, CV_8U);

    cout << "src2: " << src2 << endl;
    cout << "dst: " << dst << endl;

    cout << "cvRound(2.5): << " << cvRound(2.5) << endl;
    cout << "cvRound(2.51): << " << cvRound(2.51) << endl;
    cout << "cvRound(3.4999): << " << cvRound(3.4999) << endl;
    cout << "cvRound(3.5): << " << cvRound(3.5) << endl;
}
