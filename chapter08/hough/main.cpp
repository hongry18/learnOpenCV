#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;

void houghLines();
void houghLineSegments();
void houghCircles();

int main(void) {
    houghLines();
    houghLineSegments();
    houghCircles();

    return 0;
}

void houghLines() {
    cv::Mat src = cv::imread("building.jpg", 0);
    if (!src.data) {
        return;
    }

    cv::Mat edge;
    cv::Canny(src, edge, 50, 150);

    vector<cv::Vec2f> lines;
    cv::HoughLines(edge, lines, 1, CV_PI/180, 250);

    cv::Mat dst;
    cv::cvtColor(edge, dst, cv::COLOR_GRAY2BGR);

    for (int i=0; i<lines.size(); i++) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        float cosT = cos(theta);
        float sinT = sin(theta);
        float x0 = rho * cosT;
        float y0 = rho * sinT;
        float alpha = 1000;

        cv::Point p1(cvRound(x0 - alpha * sinT), cvRound(y0 + alpha * cosT));
        cv::Point p2(cvRound(x0 + alpha * sinT), cvRound(y0 - alpha * cosT));
        cv::line(dst, p1, p2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void houghLineSegments() {
    cv::Mat src = cv::imread("building.jpg", 0);
    if (!src.data) {
        return;
    }

    cv::Mat edge;
    cv::Canny(src, edge, 50, 150);

    vector<cv::Vec4i> lines;
    cv::HoughLinesP(edge, lines, 1, CV_PI/180, 160, 50, 5);

    cv::Mat dst;
    cv::cvtColor(edge, dst, cv::COLOR_GRAY2BGR);

    for (cv::Vec4i l : lines) {
        cv::line(dst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void houghCircles() {
    cv::Mat src = cv::imread("coins.png", 0);
    if (!src.data) {
        return;
    }

    cv::Mat blurred;
    cv::blur(src, blurred, cv::Size(3,3));

    vector<cv::Vec3f> circles;
    cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1, 50, 150, 30);

    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);

    for(cv::Vec3f c : circles) {
        cv::Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        cv::circle(dst, center, radius, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}
