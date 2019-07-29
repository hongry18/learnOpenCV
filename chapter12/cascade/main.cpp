#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void detectFace();
void detectEyes();

string imgPath = "./kids.png";

int main(void) {
    detectFace();
    detectEyes();

    return 0;
}

void detectFace() {
    cv::Mat src = cv::imread(imgPath);
    if (!src.data) {
        cout << "image can not load " << imgPath << endl;
        return;
    }

    cv::CascadeClassifier classifier("haarcascade_frontalface_default.xml");
    if (classifier.empty()) {
        cout << "can not load xml file" << endl;
        return;
    }

    vector<cv::Rect> faces;
    classifier.detectMultiScale(src, faces);

    for (cv::Rect r : faces) {
        cv::rectangle(src, r, cv::Scalar(255, 0, 255), 2);
    }

    cv::imshow("src", src);
    cv::waitKey();
    cv::destroyAllWindows();
}

void detectEyes() {
    cv::Mat src = cv::imread(imgPath);
    if (!src.data) {
        cout << "image can not load " << imgPath << endl;
        return;
    }

    cv::CascadeClassifier faceClassifier("haarcascade_frontalface_default.xml");
    cv::CascadeClassifier eyesClassifier("haarcascade_eye.xml");

    if (faceClassifier.empty() || eyesClassifier.empty()) {
        cout << "can not load xml file" << endl;
        return;
    }

    vector<cv::Rect> faces;
    faceClassifier.detectMultiScale(src, faces);

    for (cv::Rect r : faces) {
        cv::rectangle(src, r, cv::Scalar(255, 0, 255), 2);

        cv::Mat roi = src(r);
        vector<cv::Rect> eyes;
        eyesClassifier.detectMultiScale(roi, eyes);

        for (cv::Rect eye : eyes) {
            cv::Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
            cv::circle(roi, center, eye.width / 2, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
        }
    }

    cv::imshow("src", src);
    cv::waitKey();
    cv::destroyAllWindows();
}
