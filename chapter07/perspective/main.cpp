#include <iostream>
#include "opencv2/opencv.hpp"

cv::Mat src;
cv::Point2f sp[4], dp[4];

void onMouse(int e, int x, int y, int f, void* d);

int main(void) {
    src = cv::imread("./card.bmp");
    if (!src.data) {
        return -1;
    }

    cv::namedWindow("src");
    cv::setMouseCallback("src", onMouse);

    cv::imshow("src", src);
    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}

void onMouse(int e, int x, int y, int f, void* d) {
    static int cnt = 0;

    if (e != cv::EVENT_LBUTTONDOWN) {
        return;
    }

    if (cnt > 3) {
        return;
    }

    sp[cnt++] = cv::Point2f(x, y);

    cv::circle(src, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);

    if (cnt != 4) {
        return;
    }

    int w = 200;
    int h = 300;

    dp[0] = cv::Point2f(0,0);
    dp[1] = cv::Point2f(w-1, 0);
    dp[2] = cv::Point2f(w-1, h-1);
    dp[3] = cv::Point2f(0, h-1);

    cv::Mat pers = getPerspectiveTransform(sp, dp);

    cv::Mat dst;
    cv::warpPerspective(src, dst, pers, cv::Size(w, h));

    cv::imshow("dst", dst);
}
