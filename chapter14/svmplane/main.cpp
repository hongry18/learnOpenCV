#include <iostream>
#include "opencv2/opencv.hpp"

int main(void) {
    cv::Mat train = (cv::Mat_<float>(8,2) << 150, 200, 200, 250, 100, 250, 150, 300, 350, 100, 400, 200, 400, 300, 350, 400);
    cv::Mat label = cv::Mat_<int>({8, 1}, {0, 0, 0, 0, 1, 1, 1, 1});

    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::RBF);
    svm->trainAuto(train, cv::ml::ROW_SAMPLE, label);

    cv::Mat img = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);

    for (int y=0; y<img.rows; y++) {
        for (int x=0; x<img.cols; x++) {
            cv::Mat test = cv::Mat_<float>({1,2}, {(float)x, (float)y});
            int res = cvRound(svm->predict(test));

            if (res == 0) {
                img.at<cv::Vec3b>(y, x) = cv::Vec3b(128, 128, 255);
            } else {
                img.at<cv::Vec3b>(y, x) = cv::Vec3b(128, 255, 128);
            }
        }
    }

    for (int i=0; i<train.rows; i++) {
        int x = cvRound(train.at<float>(i, 0));
        int y = cvRound(train.at<float>(i, 1));
        int l = label.at<int>(i,0);

        if (l==0) {
            cv::circle(img, cv::Point(x,y), 5, cv::Scalar(0, 0, 128), -1, cv::LINE_AA);
        } else {
            cv::circle(img, cv::Point(x,y), 5, cv::Scalar(0, 0, 128), -1, cv::LINE_AA);
        }
    }

    cv::imshow("svm", img);
    cv::waitKey();

    return 0;
}
