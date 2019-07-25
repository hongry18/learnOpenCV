#include <iostream>
#include "opencv2/opencv.hpp"

using std::string;
using std::cout;
using std::endl;

string fn = "lenna.bmp";

void brightness1();
void brightness2();
void brightness3();
void brightness4();
void brightness5();
void brightness6();
void onBrightness(int p, void* a);

int main(void) {
    brightness1();
    brightness2();
    brightness3();
    brightness4();
    brightness5();
    brightness6();

    return 0;
}

void brightness1() {
    cv::Mat src = cv::imread(fn, 0);
    if (!src.data) {
        return;
    }

    cv::Mat dst = src+100;
    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void brightness2() {
    cv::Mat src = cv::imread(fn, 0);
    if (!src.data) {
        return;
    }

    cv::Mat dst(src.size(), src.type());
    for (int i=0; i<src.rows; i++) {
        for (int j=0; j<src.cols; j++) {
            dst.at<uchar>(i,j) = src.at<uchar>(i,j) + 100;
        }
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void brightness3() {
    cv::Mat src = cv::imread(fn, 0);
    if (!src.data) {
        return;
    }

    cv::Mat dst(src.size(), src.type());
    for (int i=0; i<src.rows; i++) {
        for (int j=0; j<src.cols; j++) {
            dst.at<uchar>(i,j) = cv::saturate_cast<uchar>(src.at<uchar>(i,j) +100);
        }
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void brightness4() {
    cv::Mat src = cv::imread(fn, 0);
    if (!src.data) {
        return;
    }

    cv::namedWindow("dst");
    cv::createTrackbar("Brightness", "dst", 0, 100, onBrightness, (void*)&src);
    onBrightness(0, (void*)&src);
    cv::waitKey();
    cv::destroyAllWindows();
}

void brightness5() {
    cv::Mat src = cv::imread(fn, 0);
    if (!src.data) {
        return;
    }

    cv::Mat dst(src.size(), src.type());

    uchar* sd = src.data;
    uchar* dd = dst.data;
    int size = src.rows * src.cols * src.channels();

    for (int i=0; i<size; i++) {
        dd[i] = cv::saturate_cast<uchar>(sd[i] + 100);
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void brightness6() {
    cv::Mat src = cv::imread(fn, 0);
    if (!src.data) {
        return;
    }

    cv::Mat dst(src.size(), src.type());

    uchar* sd = src.data;
    uchar* dd = dst.data;
    int size = src.rows * src.cols * src.channels();

    for (int i=0; i<size; i++) {
        int rr = (int)sd[i] + 100;
        dd[i] = rr > 255 ? 255 : rr;
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void onBrightness(int p, void* a) {
    cv::Mat src = *(cv::Mat*)a;
    cv::Mat dst = src + p;
    cv::imshow("dst", dst);
}
