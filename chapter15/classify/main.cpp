#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

int main(int argc, char** argv) {
    cv::Mat src;
    if (argc < 2) {
        src = cv::imread("./space_shuttle.jpg", 1);
    } else {
        src = cv::imread(argv[1], 1);
    }

    if (!src.data) {
        cout << "can not load image" << endl;
        return -1;
    }

    cv::dnn::Net net = cv::dnn::readNet("bvlc_googlenet.caffemodel", "deploy.prototxt");

    if (net.empty()) {
        cout << "Network load failed" << endl;
        return -1;
    }

    ifstream fp("classification_classes_ILSVRC2012.txt");

    if (!fp.is_open()) {
        cout << "can not opened file" << endl;
        return -1;
    }

    vector<string> classNames;
    string name;
    while(!fp.eof()) {
        getline(fp, name);
        if (!name.length()) {
            continue;
        }
        classNames.push_back(name);
    }

    fp.close();

    cv::Mat inputBlob, prob;
    inputBlob = cv::dnn::blobFromImage(src, 1, cv::Size(224, 224), cv::Scalar(104, 117, 123));
    net.setInput(inputBlob, "data");
    prob = net.forward();

    double maxVal;
    cv::Point maxLoc;
    cv::minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);

    string str = cv::format("%s (%4.2lf%%)", classNames[maxLoc.x].c_str(), maxVal * 100);
    cv::putText(src, str, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255));

    cv::imshow("src", src);
    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}
