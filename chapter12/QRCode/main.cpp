#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void decodeQRCode();

int main(void) {
    decodeQRCode();

    return 0;
}

void decodeQRCode() {
    cv::VideoCapture cap(1);

    if (!cap.isOpened()) { 
        cout << "camera can not opened" << endl;
        return;
    }

    cv::QRCodeDetector detector;
    cv::Mat f;
    while (1) {
        if (cv::waitKey(10) == 27) {
            break;
        }

        cap.read(f);
        if (!f.data) {
            break;
        }

        vector<cv::Point> pts;
        string info = detector.detectAndDecode(f, pts);

        if (info.empty()) {
            cv::imshow("f", f);
            continue;
        }

        cv::polylines(f, pts, true, cv::Scalar(0, 0, 255), 2);
        cv::putText(f, info, cv::Point(10, 30), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 255));

        cv::imshow("f", f);
    }
}
