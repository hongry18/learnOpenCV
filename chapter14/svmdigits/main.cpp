#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::vector;

cv::Ptr<cv::ml::SVM> trainHogSvm(const cv::HOGDescriptor& hog);
void onMouse(int e, int x, int y, int f, void* d);

int main(void) {
    cv::HOGDescriptor hog(cv::Size(20, 20), cv::Size(10, 10), cv::Size(5, 5), cv::Size(5, 5), 9);

    cv::Ptr<cv::ml::SVM> svm = trainHogSvm(hog);
    if (svm.empty()) {
        cout << "training failed" << endl;
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
            cv::Mat imgResize;

            cv::resize(img, imgResize, cv::Size(20, 20), 0, 0, cv::INTER_AREA);

            vector<float> desc;
            hog.compute(imgResize, desc);

            cv::Mat descMat(desc);
            int res = cvRound(svm->predict(descMat.t()));
            cout << res << endl;

            img.setTo(0);
            cv::imshow("img", img);
        }
    }

    return 0;
}

cv::Ptr<cv::ml::SVM> trainHogSvm(const cv::HOGDescriptor& hog) {
    cv::Mat digits = cv::imread("./digits.png", 0);

    if (!digits.data) {
        cout << "can not opened image" << endl;
        return 0;
    }

    cv::Mat hogs, labels;

    for (int i=0; i<50; i++) {
        for (int j=0; j<100; j++) {
            cv::Mat roi = digits(cv::Rect(j * 20, i * 20, 20, 20));

            vector<float> desc;
            hog.compute(roi, desc);
            cv::Mat descMat(desc);

            hogs.push_back(descMat.t());
            labels.push_back(i/5);
        }
    }

    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::Types::C_SVC);
    svm->setKernel(cv::ml::SVM::KernelTypes::RBF);
    svm->setC(2.5);
    svm->setGamma(0.50625);
    svm->train(hogs, cv::ml::ROW_SAMPLE, labels);

    return svm;
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
