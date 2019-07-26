#include <iostream>
#include "opencv2/opencv.hpp"

int main(void) {
    cv::Mat src1, src2;

    src1 = cv::imread("./lenna256.bmp", 0);
    src2 = cv::imread("./square.bmp", 0);

    if (!src1.data || !src2.data) {
        return -1;
    }

    cv::imshow("src1", src1);
    cv::imshow("src2", src2);

    cv::Mat dst1, dst2, dst3, dst4;

    cv::add(src1, src2, dst1);
    cv::addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
    cv::subtract(src1, src2, dst3);
    cv::absdiff(src1, src2, dst4);

    cv::imshow("dst1", dst1);
    cv::imshow("dst2", dst2);
    cv::imshow("dst3", dst3);
    cv::imshow("dst4", dst4);

    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}
