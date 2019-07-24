#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

void vecOp();
void scalarOp();

int main(void) {
    vecOp();
    scalarOp();

    return 0;
}

void vecOp() {
    cv::Vec3b p1, p2(0, 0, 255);
    p1[0] = 100;
    cout << "p1: " << p1 << "\n\n";
    cout << "p2: " << p2 << "\n\n";
    cout << endl;
}

void scalarOp() {
    cv::Scalar g = 128;
    cout << "g :" << g << "\n\n";

    cv::Scalar y(0, 255, 255);
    cout << "y: " << y << "\n\n";

    cv::Mat i1(256,256,CV_8UC3, y);
    for (int i=0; i<4; i++) {
        cout << y.val[i] << ", " << y[i] << "\n";
    }

    cout << endl;
}
