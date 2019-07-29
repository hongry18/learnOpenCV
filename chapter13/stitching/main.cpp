#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;

string paths[] = {"./img1.jpg", "./img2.jpg", "./img3.jpg"};

int main(void) {
    vector<cv::Mat> imgs;

    for (int i=0; i<3; i++) {
        imgs.push_back(cv::imread(paths[i]));
    }

    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create();

    cv::Mat dst;
    cv::Stitcher::Status status = stitcher->stitch(imgs, dst);

    if (status != cv::Stitcher::Status::OK) {
        return -1;
    }

    cv::imwrite("result.png", dst);
    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}
