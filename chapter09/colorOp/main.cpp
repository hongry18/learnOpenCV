#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;

void colorOp();
void colorInverse1();
void colorInverse2();
void colorInverse3();
void colorGrayscale();
void colorSplit();

int main(void) {
    colorOp();
    colorInverse1();
    colorInverse2();
    colorInverse3();
    colorGrayscale();
    colorSplit();

    return 0;
}

void colorOp() {
    cv::Mat src = cv::imread("./butterfly.jpg", 1);
    if (!src.data) {
        return;
    }

    uchar *data = src.data;
    int len = src.rows * src.cols * src.channels();

    for (int i=0; i<len; i += 3) {
    }
}

void colorInverse1() {
    cv::Mat src = cv::imread("./butterfly.jpg", 1);
    if (!src.data) {
        return;
    }

    cv::Mat dst(src.size(), src.type());
    uchar *sData = src.data;
    uchar *dData = dst.data;
    int len = src.rows * src.cols * src.channels();

    for (int i=0; i<len; i += 3) {
        dData[i] = 255 - sData[i];
        dData[i+1] = 255 - sData[i+1];
        dData[i+2] = 255 - sData[i+2];
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void colorInverse2() {
    cv::Mat src = cv::imread("./butterfly.jpg", 1);
    if (!src.data) {
        return;
    }

    cv::Mat dst(src.size(), src.type());
    uchar *sData = src.data;
    uchar *dData = dst.data;
    int channel = src.channels();

    for (int y=0; y<src.rows; y++) {
        for (int x=0; x<src.cols; x++) {
            int addr = x * y * channel;

            dData[addr] = 255 - sData[addr];
            dData[addr+1] = 255 - sData[addr+1];
            dData[addr+2] = 255 - sData[addr+2];
        }
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void colorInverse3() {
    cv::Mat src = cv::imread("./butterfly.jpg", 1);
    if (!src.data) {
        return;
    }

    cv::Mat dst(src.size(), src.type());

    for (int y=0; y<src.rows; y++) {
        for (int x=0; x<src.cols; x++) {
            cv::Vec3b& p1 = src.at<cv::Vec3b>(y, x);
            cv::Vec3b& p2 = dst.at<cv::Vec3b>(y, x);

            p2[0] = 255 - p1[0];
            p2[1] = 255 - p1[1];
            p2[2] = 255 - p1[2];
        }
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void colorGrayscale() {
    cv::Mat src = cv::imread("./butterfly.jpg", 1);
    if (!src.data) {
        return;
    }

    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void colorSplit() {
    cv::Mat src = cv::imread("./candies.png", 1);
    if (!src.data) {
        return;
    }

    vector<cv::Mat> planes;
    cv::split(src, planes);

    cv::imshow("src", src);
    cv::imshow("b", planes[0]);
    cv::imshow("g", planes[1]);
    cv::imshow("r", planes[2]);
    cv::waitKey();
    cv::destroyAllWindows();
}
