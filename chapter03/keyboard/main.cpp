#include <iostream>
#include "opencv2/opencv.hpp"

int main(void) {
    cv::Mat src = cv::imread("./lenna.bmp");

    if (!src.data) {
        return -1;
    }

    cv::namedWindow("img");
    cv::imshow("img", src);

    while(true) {
        int k = cv::waitKey();

        if (k=='i' || k=='I') {
            src = ~src;
            cv::imshow("img", src);
        } else if (k==27 || k == 'q' || k == 'Q') {
            break;
        }
    }

    return 0;
}
