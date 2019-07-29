#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void cornerHarris();
void cornerFast();

string imgPath = "./building.jpg";

int main(void) {
    cornerHarris();
    cornerFast();

    return 0;
}

void cornerHarris() {
    cv::Mat src = cv::imread(imgPath, 0);
    if (!src.data) {
        return;
    }

    cv::Mat harris, harrisNorm, dst;
    cv::cornerHarris(src, harris, 3, 3, 0.04);
    cv::normalize(harris, harrisNorm, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);

    int width = harrisNorm.step1();
    float *harrisData = (float*)harris.data;

    for (int y=0; y<harris.rows - 1; y++) {
        for (int x=0; x<harris.cols - 1; x++) {

            if (harrisNorm.data[ y * width + x ] < 121 ) {
                continue;
            }

            if(harrisData[y * width + x] > harrisData[ (y+1) * width + x ]
            && harrisData[y * width + x] > harrisData[ (y-1) * width + x ]
            && harrisData[y * width + x] > harrisData[ y * width + (x-1) ]
            && harrisData[y * width + x] > harrisData[ y * width + (x+1) ]) {
                cv::circle(dst, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), 2);
            }
        }
    }

    for (int y=0; y<harris.rows - 1; y++) {
        for (int x=0; x<harris.cols - 1; x++) {
            if (harrisNorm.at<uchar>(y, x) < 121) {
                continue;
            }

            if ( harris.at<float>(y, x) > harris.at<float>(y-1, x)
            && harris.at<float>(y, x) > harris.at<float>(y+1, x)
            && harris.at<float>(y, x) > harris.at<float>(y, x-1)
            && harris.at<float>(y, x) > harris.at<float>(y, x+1) ) {
                cv::circle(dst, cv::Point(x, y), 5, cv::Scalar(255, 0, 0), 1);
            }
        }
    }

    cv::imshow("src", src);
    cv::imshow("harrisNorm", harrisNorm);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();

}

void cornerFast() {
    cv::Mat src = cv::imread(imgPath, 0);
    if (!src.data) {
        return;
    }

    cv::Mat dst;
    vector<cv::KeyPoint> kpts;

    cv::FAST(src, kpts, 60, true);
    cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);

    for (cv::KeyPoint kpt : kpts) {
        cv::Point p(cvRound(kpt.pt.x), cvRound(kpt.pt.y));
        cv::circle(dst, p, 5, cv::Scalar(0, 0, 255), 2);
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}
