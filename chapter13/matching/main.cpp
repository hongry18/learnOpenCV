#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;

string path1 = "./box.png";
string path2 = "./box_in_scene.png";

void keypointMatching();
void goodMatching();
void findHomography();

int main(void) {
    keypointMatching();
    goodMatching();
    findHomography();

    return 0;
}

void keypointMatching() {
    cv::Mat src1, src2;
    src1 = cv::imread(path1, 0);
    src2 = cv::imread(path2, 0);

    if (!src1.data || !src2.data) {
        cout << "can not load images" << endl;
        return;
    }

    cv::Ptr<cv::Feature2D> feature = cv::ORB::create();

    vector<cv::KeyPoint> kpts1, kpts2;
    cv::Mat desc1, desc2;
    feature->detectAndCompute(src1, cv::Mat(), kpts1, desc1);
    feature->detectAndCompute(src2, cv::Mat(), kpts2, desc2);
    cout << "desc1 size: " << desc1.size() << endl;
    cout << "desc2 size: " << desc2.size() << endl;

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NORM_HAMMING);
    vector<cv::DMatch> matches;
    matcher->match(desc1, desc2, matches);

    cv::Mat dst;
    cv::drawMatches(src1, kpts1, src2, kpts2, matches, dst);

    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void goodMatching() {
    cv::Mat src1, src2;
    src1 = cv::imread(path1, 0);
    src2 = cv::imread(path2, 0);

    if (!src1.data || !src2.data) {
        cout << "can not load images" << endl;
        return;
    }

    cv::Ptr<cv::Feature2D> feature = cv::ORB::create();

    vector<cv::KeyPoint> kpts1, kpts2;
    cv::Mat desc1, desc2;
    feature->detectAndCompute(src1, cv::Mat(), kpts1, desc1);
    feature->detectAndCompute(src2, cv::Mat(), kpts2, desc2);
    cout << "desc1 size: " << desc1.size() << endl;
    cout << "desc2 size: " << desc2.size() << endl;

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NORM_HAMMING);
    vector<cv::DMatch> matches;
    matcher->match(desc1, desc2, matches);

    std::sort(matches.begin(), matches.end());
    vector<cv::DMatch> goodMatches(matches.begin(), matches.begin() + 50);

    cv::Mat dst;
    cv::drawMatches(src1, kpts1, src2, kpts2, goodMatches, dst, cv::Scalar::all(-1), cv::Scalar::all(-1), vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}

void findHomography() {
    cv::Mat src1, src2;
    src1 = cv::imread(path1, 0);
    src2 = cv::imread(path2, 0);

    if (!src1.data || !src2.data) {
        cout << "can not load images" << endl;
        return;
    }

    cv::Ptr<cv::Feature2D> feature = cv::ORB::create();

    vector<cv::KeyPoint> kpts1, kpts2;
    cv::Mat desc1, desc2;
    feature->detectAndCompute(src1, cv::Mat(), kpts1, desc1);
    feature->detectAndCompute(src2, cv::Mat(), kpts2, desc2);
    cout << "desc1 size: " << desc1.size() << endl;
    cout << "desc2 size: " << desc2.size() << endl;

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NORM_HAMMING);
    vector<cv::DMatch> matches;
    matcher->match(desc1, desc2, matches);

    std::sort(matches.begin(), matches.end());
    vector<cv::DMatch> goodMatches(matches.begin(), matches.begin() + 50);

    cv::Mat dst;
    cv::drawMatches(src1, kpts1, src2, kpts2, goodMatches, dst, cv::Scalar::all(-1), cv::Scalar::all(-1), vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    vector<cv::Point2f> pts1, pts2;
    for (size_t i=0; i<goodMatches.size(); i++) {
        pts1.push_back(kpts1[goodMatches[i].queryIdx].pt);
        pts2.push_back(kpts2[goodMatches[i].trainIdx].pt);
    }

    cv::Mat H = cv::findHomography(pts1, pts2, cv::RANSAC);

    vector<cv::Point2f> corners1, corners2;
    corners1.push_back(cv::Point2f(0,0));
    corners1.push_back(cv::Point2f(src1.cols - 1.f, 0));
    corners1.push_back(cv::Point2f(src1.cols - 1.f, src1.rows - 1.f));
    corners1.push_back(cv::Point2f(0,src1.rows - 1.f));
    cv::perspectiveTransform(corners1, corners2, H);

    vector<cv::Point> cornersDst;
    for (cv::Point2f p : corners2) {
        cornersDst.push_back(cv::Point(cvRound(p.x + src1.cols), cvRound(p.y)));
    }

    cv::polylines(dst, cornersDst, true, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);

    cv::imshow("dst", dst);
    cv::waitKey();
    cv::destroyAllWindows();
}
