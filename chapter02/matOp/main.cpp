#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

void matOp1();
void matOp2();
void matOp3();
void matOp4();
void matOp5();
void matOp6();
void matOp7();
void matOp8();
void suffix();

int main() {

    matOp1();
    matOp2();
    matOp3();
    matOp4();
    matOp5();
    matOp6();
    matOp7();
    matOp8();

    return 0;
}

void suffix() {
    cv::waitKey();
    cv::destroyAllWindows();
}

void matOp1() {
    cv::Mat img1;

    cv::Mat img2(480, 640, CV_8UC1);
    cv::Mat img3(480, 640, CV_8UC3);
    cv::Mat img4(cv::Size(640, 480), CV_8UC3);
    // cv::Size(width, height)

    cv::Mat img5(480, 640, CV_8U, cv::Scalar(128));
    cv::Mat img6(480, 640, CV_8UC3, cv::Scalar(0, 0, 255));

    cv::Mat m1 = cv::Mat::zeros(3, 3, CV_32SC1);
    cv::Mat m2 = cv::Mat::ones(3, 3, CV_32FC1);
    cv::Mat m3 = cv::Mat::eye(3, 3, CV_32FC1);

    float d[] = { 1,2,3,4,5,6 };
    cv::Mat m4(2, 3, CV_32FC1, d);

    cv::Mat m5 = (cv::Mat_<float>(2, 3) << 1,2,3,4,5,6);
    cv::Mat m6 = cv::Mat_<uchar>({2,3}, {1,2,3,4,5,6});

    m4.create(256, 2546, CV_8UC3);
    m5.create(4, 4, CV_32FC1);

    m4 = cv::Scalar(255, 0, 0);
    m5.setTo(1.f);
}

void matOp2() {
    cv::Mat i1 = cv::imread("./dog.bmp");
    cv::Mat i2 = i1;
    cv::Mat i3;
    i3 = i1;

    cv::Mat i4 = i1.clone();
    cv::Mat i5;
    i1.copyTo(i5);

    i1.setTo(cv::Scalar(0, 255, 255));

    cv::imshow("1", i1);
    cv::imshow("2", i2);
    cv::imshow("3", i3);
    cv::imshow("4", i4);
    cv::imshow("5", i5);

    suffix();
}

void matOp3() {
    cv::Mat i1 = cv::imread("./cat.bmp");
    if (!i1.data) {
        return;
    }

    cv::Mat i2 = i1(cv::Rect(220, 120, 340, 240));
    cv::Mat i3 = i1(cv::Rect(220, 120, 324, 240)).clone();

    i2 = ~i2;

    cv::imshow("1", i1);
    cv::imshow("2", i2);
    cv::imshow("3", i3);

    suffix();
}

void matOp4() {
    cv::Mat i1 = cv::Mat::zeros(3, 4, CV_8UC1);
    uchar *d = i1.data;

    for (int i=0; i<i1.rows; i++) {
        for (int j=0; j<i1.cols; j++) {
            i1.at<uchar>(i, j)++;
        }
    }

    for (int i=0; i<i1.rows; i++) {
        uchar *p = i1.ptr<uchar>(i);
        for (int j=0; j<i1.cols; j++) {
            p[j]++;
        }
    }

    for (cv::MatIterator_<uchar> it = i1.begin<uchar>(); it != i1.end<uchar>(); it++) {
        (*it)++;
    }

    int len = i1.rows * i1.cols * i1.channels();
    for (int i=0; i<len; i++) {
        d[i]++;
    }

    cout << i1 << endl;
}

void matOp5() {
    cv::Mat img = cv::imread("lenna.bmp");

    printf("width: %d\n", img.cols);
    printf("height: %d\n", img.rows);
    printf("channels: %d\n", img.channels());

    float d[] = {2.f, 1.414f, 3.f, 1.732f};
    cv::Mat m(2,2,CV_32FC1, d);

    cout << m << endl;
}

void matOp6() {
    float d[] = {1,1,2,3};
    cv::Mat m1(2,2,CV_32FC1, d);
    cout << "m1: " << m1 << endl;

    cv::Mat m2 = m1.inv();
    cout << "m2: " << m2 << endl;

    cout << "m1.t()\n " << m1.t() << endl;
    cout << "m1+3\n " << m1 + 3 << endl;
    cout << "m1.t()\n " << m1 << endl;
    cout << "m1.t()\n " << m1 << endl;
}

void matOp7() {
    cv::Mat img = cv::imread("./lenna.bmp", cv::IMREAD_GRAYSCALE);

    cv::Mat imgf;
    img.convertTo(imgf, CV_32FC1);

    uchar d[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    cv::Mat m1(3,4,CV_8U,d);
    cv::Mat m2 = m1.reshape(0,1);

    cout << m1 << endl;
    cout << m2 << endl;

    m1.resize(5, 100);
    cout << m1 << endl;

    cv::Mat m3 = cv::Mat::ones(1, 4, CV_8U) * 255;
    m1.push_back(m3);
    cout << m1 << endl;
}

void matOp8() {
    cv::Mat m1(3, 3, CV_8U);
    cv::Mat m2(3, 3, CV_8UC3);

    cout << "m1 step1(): " << m1.step1() << endl;
    cout << "m2 step1(): " << m2.step1() << endl;
}
