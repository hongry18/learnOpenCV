#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

cv::Ptr<cv::ml::KNearest> trainKnn();
void onMouse(int e, int x, int y, int f, void* d);

int main(void) {
    cv::Ptr<cv::ml::KNearest> knn = trainKnn();
    if (knn.empty()) {
        cout << "traing failed!" << endl;
        return -1;
    }

    cv::Mat img = cv::Mat::zeros(400, 400, CV_8U);
    cv::imshow("img", img);
    cv::setMouseCallback("img", onMouse, (void*)&img);

    while(1) {
        int c = cv::waitKey(1);

        if (c==27) {
            break;
        }

        if (c == ' ') {
            cv::Mat imgResize, imgFloat, imgFlatten, res;

            cv::resize(img, imgResize, cv::Size(20, 20), 0, 0, cv::INTER_AREA);
            imgResize.convertTo(imgFloat, CV_32F);
            imgFlatten = imgFloat.reshape(1, 1);

            knn -> findNearest(imgFlatten, 3, res);
            cout << cvRound(res.at<float>(0,0)) << endl;

            img.setTo(0);
            cv::imshow("img", img);
        }
    }
    return 0;
}

cv::Ptr<cv::ml::KNearest> trainKnn() {
    cv::Mat digits = cv::imread("./digits.png", 0);

    if (!digits.data) {
        cout << "can not opened image" << endl;
        return 0;
    }

    cv::Mat imgs, labels;

    for (int i=0; i<50; i++) {
        for (int j=0; j<100; j++) {
            cv::Mat roi, roiFloat, roiFlatten;
            roi = digits(cv::Rect(j*20, i*20, 20, 20));
            roi.convertTo(roiFloat, CV_32F);
            roiFlatten = roiFloat.reshape(1, 1);

            imgs.push_back(roiFlatten);
            labels.push_back(i/5);
        }
    }

    cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
    knn->train(imgs, cv::ml::ROW_SAMPLE, labels);

    return knn;
}

cv::Point ptPrev(-1, -1);

void onMouse(int e, int x, int y, int f, void* d) {
    cv::Mat img = *(cv::Mat*)d;

    if (e == cv::EVENT_LBUTTONDOWN) {
        ptPrev = cv::Point(x, y);
    } else if (e == cv::EVENT_LBUTTONUP) {
        ptPrev = cv::Point(-1, -1);
    } else if (e == cv::EVENT_MOUSEMOVE && (f & cv::EVENT_FLAG_LBUTTON)) {
        cv::line(img, ptPrev, cv::Point(x, y), cv::Scalar::all(255), 40, cv::LINE_AA, 0);
        ptPrev = cv::Point(x, y);
        cv::imshow("img", img);
    }
}
