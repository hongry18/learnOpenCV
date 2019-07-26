#include <iostream>
#include "opencv2/opencv.hpp"

void filterEmbossing();

int main(void) {
    filterEmbossing();

    return 0;
}

void filterEmbossing() {
    cv::Mat src = cv::imread("./rose.bmp", 0);

    if (!src.data) {
        return;
    }

    float d[] = {-1, -1, 0, -1, 0, 1, 0, 1, 1};
    cv::Mat emboss(3,3,CV_32F, d);

    cv::Mat dst;
    cv::filter2D(src, dst, -1, emboss, cv::Point(-1, -1), 128);

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}
