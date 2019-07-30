#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

void onMouse(int e, int x, int y, int f, void* d);

int main(void) {
    cv::dnn::Net net = cv::dnn::readNet("./mnist_cnn.pb");
    if (net.empty()) {
        return -1;
    }

    cv::Mat img = cv::Mat::zeros(400, 400, CV_8U);

    cv::imshow("img", img);
    cv::setMouseCallback("img", onMouse, (void*)&img);

    while(1) {
        int k = cv::waitKey(1);

        if (k==27) {
            break;
        }

        if (k!=' ') {
            continue;
        }

        cv::Mat blob = cv::dnn::blobFromImage(img, 1/255.f, cv::Size(28, 28));
        net.setInput(blob);
        cv::Mat prob = net.forward();

        double maxVal;
        cv::Point maxLoc;
        cv::minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
        int digits = maxLoc.x;

        cout << digits << " (" << maxVal * 100 << "%)" << endl;

        img.setTo(0);
        cv::imshow("img", img);
    }

    return 0;
}

cv::Point pt(-1, 1);

void onMouse(int e, int x, int y, int f, void* d) {
    cv::Mat img = *(cv::Mat*)d;

    if(e==cv::EVENT_LBUTTONDOWN) {
        pt = cv::Point(x,y);
    } else if (e==cv::EVENT_LBUTTONUP) {
        pt = cv::Point(x,y);
    } else if (e==cv::EVENT_MOUSEMOVE && (f & cv::EVENT_FLAG_LBUTTON)) {
        cv::Point cp(x,y);
        cv::line(img, pt, cp, cv::Scalar::all(255), 40, cv::LINE_AA, 0);
        pt = cp;
        cv::imshow("img", img);
    }
}
