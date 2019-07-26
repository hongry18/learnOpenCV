#include <iostream>
#include "opencv2/opencv.hpp"

void unsharpMask();

int main(void) {
    unsharpMask();

    return 0;
}

void unsharpMask() {
    cv::Mat src = cv::imread("./rose.bmp", 0);

    if (!src.data) {
        return;
    }

    cv::imshow("src", src);

    for (int sigma=1; sigma<6; sigma++) {
        cv::Mat blurred;
        cv::GaussianBlur(src, blurred, cv::Size(), sigma);

        float alpha = 1.f;
        cv::Mat dst = (1+alpha) * src - alpha * blurred;

        std::string desc = cv::format("sigma: %d", sigma);
        cv::putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255), 1, cv::LINE_AA);

        cv::imshow("dst", dst);

        cv::waitKey();
    }

    cv::destroyAllWindows();
}
