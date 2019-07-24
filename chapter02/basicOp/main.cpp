#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::string;

void pointOp();
void sizeOp();
void rectOp();
void rotatedRectOp();
void rangeOp();
void stringOp();

int main() {

    pointOp();
    sizeOp();
    rectOp();
    rotatedRectOp();
    rangeOp();
    stringOp();

    return 0;
}

void pointOp() {
    cout << "point operation" << endl;
    cv::Point p1;
    p1.x = 5;
    p1.y = 10;
    cv::Point p2(10, 30);

    cv::Point p3 = p1+p2;
    cv::Point p4 = p1*2;
    int d1 = p1.dot(p2);
    bool b1 = (p1 == p2);

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
}

void sizeOp() {
    cout << "size operation" << endl;
    cv::Size s1, s2(10, 20);
    s1.width = 5;
    s1.height = 10;

    cv::Size s3 = s1+s2;
    cv::Size s4 = s1*2;
    int area = s4.area();

    cout << "s3: " << s3 << endl;
    cout << "s4: " << s4 << endl;
}

void rectOp() {
    cout << "rect operation" << endl;
    cv::Rect r1, r2(10, 10, 60, 40);
    cv::Rect r3 = r1 + cv::Size(50, 40);
    cv::Rect r4 = r2 + cv::Point(10, 10);

    cv::Rect r5 = r3 & r4;
    cv::Rect r6 = r3 | r4;

    cout << r5 << endl;
    cout << r6 << endl;
}

void rotatedRectOp() {
    cv::RotatedRect rr1(cv::Point2f(40, 30), cv::Size2f(40, 20), 30.f);
    cv::Point2f p[4];
    rr1.points(p);

    cv::Rect br = rr1.boundingRect();
}

void rangeOp() {
    cv::Range r(0, 10);
}

void stringOp() {
    string s1 = "hello";
    string s2 = "world";
    string s3 = s1 + " " + s2;

    bool ret = ( s2 == "WORLD" );

    cv::Mat imgs[3];

    for (int i=0; i<3; i++) {
        string filename = cv::format("data%02d.bmp", i+1);
        cout << filename << endl;
    }
}
