#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::string;

const string model = "res10_300x300_ssd_iter_140000_fp16.caffemodel";
const string config = "deploy.prototxt";

int main(void) {
    cv::VideoCapture cap(1);
    if (!cap.isOpened()) {
        cout << "can not opened camera" << endl;
        return -1;
    }

    cv::dnn::Net net = cv::dnn::readNet(model, config);
    if (net.empty()) {
        cout << "can not load Network model" << endl;
        return -1;
    }

    cv::Mat f, blob, res, detect;
    while (1) {
        if (cv::waitKey(10) == 27) {
            break;
        }

        cap.read(f);
        if (!f.data) {
            break;
        }

        blob = cv::dnn::blobFromImage(f, 1, cv::Size(300, 300), cv::Scalar(104, 177, 123));
        net.setInput(blob);
        res = net.forward();
        detect = cv::Mat(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());

        for (int i=0; i<detect.rows; i++) {
            float confidence = detect.at<float>(i, 2);
            if (confidence < 0.5) {
                break;
            }

            int x1, y1, x2, y2;
            x1 = cvRound(detect.at<float>(i, 3) * f.cols);
            y1 = cvRound(detect.at<float>(i, 4) * f.rows);
            x2 = cvRound(detect.at<float>(i, 5) * f.cols);
            y2 = cvRound(detect.at<float>(i, 6) * f.rows);

            cv::rectangle(f, cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2)), cv::Scalar(0, 255, 0));
            string label = cv::format("face: %4.3f", confidence);
            cv::putText(f, label, cv::Point(x1, y1-1), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0));
        }

        cv::imshow("f", f);
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
