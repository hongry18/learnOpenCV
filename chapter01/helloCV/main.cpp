#include <iostream>
#include "opencv2/opencv.hpp"

int main(void) {
    cv::Mat src = cv::imread("./lena.jpg");

    if (!src.data) {
        return -1;
    }

    cv::imshow("src", src);
    cv::waitKey();

    return 0;
}
