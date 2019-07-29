#include <iostream>
#include "opencv2/opencv.hpp"

using std::string;
using std::vector;

void setLabel(cv::Mat& img, const vector<cv::Point>& p, const string& label) {
    cv::Rect r = cv::boundingRect(p);
    cv::rectangle(img, r, cv::Scalar(0, 0, 255), 1);
    cv::putText(img, label, r.tl(), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255));
}

int main(void) {
    cv::Mat src = cv::imread("./polygon.bmp", 1);

    if (!src.data) {
        return -1;
    }

    cv::Mat gray, bin;
    vector<vector<cv::Point>> contours;

    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, bin, 200, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    cv::findContours(bin, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    for(vector<cv::Point> contour : contours) {
        if (cv::contourArea(contour) < 400) {
            continue;
        }

        vector<cv::Point> approx;
        double epsilon = cv::arcLength(contour, true);
        cv::approxPolyDP(contour, approx, epsilon * 0.02, true);

        int approxSize = (int)approx.size();

        if (approxSize == 3) {
            setLabel(src, contour, "Triangle");
        } else if (approxSize == 4) {
            setLabel(src, contour, "Rectangle");
        } else {
            double area = cv::contourArea(contour);
            double ratio = 4. * CV_PI * area / (epsilon * epsilon);

            if (ratio < 0.86) {
                continue;
            }

            setLabel(src, contour, "Circle");
        }
    }

    cv::imshow("src", src);
    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}
