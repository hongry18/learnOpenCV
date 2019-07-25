#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

cv::Mat src;
cv::Point pt;
void onMouse(int e, int x, int y, int f, void*);

int main(void) {
    src = cv::imread("./lenna.bmp");

    if (!src.data) {
        return -1;
    }

    cv::namedWindow("img");
    cv::setMouseCallback("img", onMouse);

    cv::imshow("img", src);
    cv::waitKey();

    return 0;
}

void onMouse(int e, int x, int y, int f, void*) {
    switch(e) {
        case cv::EVENT_LBUTTONDOWN:
            pt = cv::Point(x ,y);
            cout << "event lbutton down" << pt << endl;
            break;
        case cv::EVENT_LBUTTONUP:
            cout << "event lbutton up" << pt << endl;
            break;
        case cv::EVENT_MOUSEMOVE:
            if (f & cv::EVENT_FLAG_LBUTTON) {
                cv::Point cpt(x, y);
                cv::line(src, pt, cpt, cv::Scalar(0, 255, 255), 2);
                cv::imshow("img", src);
                pt = cpt;
            }
            break;
    }
}
