#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

cv::Mat img, train, label;
cv::Ptr<cv::ml::KNearest> knn;
int kVal = 1;

void onKChanged(int, void*);
void addPoint(const cv::Point& p, int cls);
void trainAndDisplay();

int main(void) {
    img = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);
    knn = cv::ml::KNearest::create();

    cv::namedWindow("knn");
    cv::createTrackbar("k", "knn", &kVal, 5, onKChanged);

    const int NUM = 30;
    cv::Mat rn(NUM, 2, CV_32SC1);

    cv::randn(rn, 0, 50);
    for (int i=0; i<NUM; i++) {
        addPoint(cv::Point(rn.at<int>(i, 0) + 150, rn.at<int>(i,1) + 150), 0);
    }

    cv::randn(rn, 0, 50);
    for (int i=0; i<NUM; i++) {
        addPoint(cv::Point(rn.at<int>(i, 0) + 350, rn.at<int>(i,1) + 150), 1);
    }

    cv::randn(rn, 0, 70);
    for (int i=0; i<NUM; i++) {
        addPoint(cv::Point(rn.at<int>(i, 0) + 250, rn.at<int>(i,1) + 400), 2);
    }

    trainAndDisplay();
    cv::waitKey();

    return 0;
}

void onKChanged(int, void*) {
    if (kVal < 1) {
        kVal = 1;
    }

    trainAndDisplay();
}

void addPoint(const cv::Point& p, int cls) {
    cv::Mat newSample = (cv::Mat_<float>(1,2) << p.x, p.y);
    train.push_back(newSample);
    cv::Mat newLabel = (cv::Mat_<int>(1,1) << cls);
    label.push_back(newLabel);
}

void trainAndDisplay() {
    knn -> train(train, cv::ml::ROW_SAMPLE, label);

    for (int y=0; y<img.rows; y++) {
        for (int x=0; x<img.cols; x++) {
            cv::Mat sample = (cv::Mat_<float>(1,2) << x, y);

            cv::Mat res;
            knn -> findNearest(sample, kVal, res);

            int response = cvRound(res.at<float>(0, 0));
            if (response == 0) {
                img.at<cv::Vec3b>(y, x) = cv::Vec3b(128, 128, 255);
            } else if (response == 1) {
                img.at<cv::Vec3b>(y, x) = cv::Vec3b(128, 128, 128);
            } else if (response == 2) {
                img.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 128, 128);
            }
        }
    }

    for (int i=0; i<train.rows; i++) {
        int x = cvRound(train.at<float>(i, 0));
        int y = cvRound(train.at<float>(i, 1));
        int l = label.at<int>(i, 0);

        if (l == 0) {
            cv::circle(img, cv::Point(x, y), 5, cv::Scalar(0, 0, 128), -1, cv::LINE_AA);
        } else if (l == 1) {
            cv::circle(img, cv::Point(x, y), 5, cv::Scalar(0, 128, 0), -1, cv::LINE_AA);
        } else if (l == 2) {
            cv::circle(img, cv::Point(x, y), 5, cv::Scalar(128, 0, 0), -1, cv::LINE_AA);
        }
    }

    cv::imshow("knn", img);
}
