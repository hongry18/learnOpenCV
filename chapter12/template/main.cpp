#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void templateMatching();

int main(void) {
    templateMatching();

    return 0;
}

void templateMatching() {
    cv::Mat src = cv::imread("circuit.bmp");
    cv::Mat tmpl = cv::imread("crystal.bmp");

    if (!src.data || !tmpl.data) {
        cout << "can not load images" << endl;
        return;
    }

    src += cv::Scalar(50, 50, 50);
    cv::Mat noise(src.size(), CV_32SC3);
    cv::randn(noise, 0, 10);
    cv::add(src, noise, src, cv::Mat(), CV_8UC3);

    cv::Mat res, resNorm;
    cv::matchTemplate(src, tmpl, res, cv::TM_CCOEFF_NORMED);
    cv::normalize(res, resNorm, 0, 255, cv::NORM_MINMAX, CV_8U);

    double maxv;
    cv::Point maxLoc;
    cv::minMaxLoc(res, 0, &maxv, 0, &maxLoc);
    cout << "maxv: " << maxv << endl;

    cv::rectangle(src, cv::Rect(maxLoc.x, maxLoc.y, tmpl.cols, tmpl.rows), cv::Scalar(0, 0, 255), 2);

    cv::imshow("src", src);
    cv::imshow("tmpl", tmpl);
    cv::imshow("resNorm", resNorm);

    cv::waitKey();
    cv::destroyAllWindows();
}
