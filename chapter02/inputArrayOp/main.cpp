#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

void inputArrayOp();
void printMat(cv::InputArray& _mat);

int main(void) {
    inputArrayOp();
    return 0;
}

void inputArrayOp() {
    uchar data[] = { 1,2,3,4,5,6 };
    cv::Mat m(2, 3, CV_8U, data);
    printMat(m);

    std::vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
    printMat(vec1);
}

void printMat(cv::InputArray& _mat) {
    cv::Mat m = _mat.getMat();
    cout << m << endl;
}
