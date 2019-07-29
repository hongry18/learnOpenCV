#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;


string imgPath = "./box_in_scene.png";

void detectKeypoints();

int main(void) {
    detectKeypoints();

    return 0;
}

void detectKeypoints() {
    cv::Mat src = cv::imread(imgPath, 0);
    if (!src.data) {
        return;
    }

    cv::Ptr<cv::Feature2D> feature = cv::ORB::create();

    vector<cv::KeyPoint> kpts;
    feature->detect(src, kpts);

    cv::Mat desc;
    feature->compute(src, kpts, desc);

    cout << "kpts size: " << kpts.size() << endl;
    cout << "desc size: " << desc.size() << endl;

    cv::Mat dst;
    cv::drawKeypoints(src, kpts, dst, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}
