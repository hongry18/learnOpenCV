#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::cout;
using std::endl;

int main(void) {
    cv::VideoCapture cap("./vtest.mp4");
    if (!cap.isOpened()) {
        cout << "can not opened video(vtest.mp4)" << endl;
        return -1;
    }

    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

    cv::Mat f;
    while(1) {
        if (cv::waitKey(10) == 27) {
            cout << "bye bye" << endl;
            break;
        }

        cap.read(f);
        if (!f.data) {
            cout << "empty data" << endl;
            break;
        }

        vector<cv::Rect> detected;
        hog.detectMultiScale(f, detected);

        for (cv::Rect r : detected) {
            cv::Scalar c(rand() % 256, rand() % 256, rand() % 256);
            cv::rectangle(f, r, c, 3);
        }

        cv::imshow("f", f);
    }

    return 0;
}
