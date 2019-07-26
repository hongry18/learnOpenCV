#include <iostream>
#include "opencv2/opencv.hpp"

void affineTransform();
void affineTranslation();
void affineShear();
void affineScale();
void affineRotation();
void affineFlip();

int main(void) {
    affineTransform();
    affineTranslation();
    affineShear();
    affineScale();
    affineRotation();
    affineFlip();

    return 0;
}

void affineTransform() {
    cv::Mat src = cv::imread("tekapo.bmp");
    if (!src.data) {
        return;
    }

    cv::Point2f sp[3], dp[3];
    sp[0] = cv::Point2f(0,0);
    sp[1] = cv::Point2f(src.cols-1,0);
    sp[2] = cv::Point2f(src.cols-1,src.rows-1);
    dp[0] = cv::Point2f(50,50);
    dp[1] = cv::Point2f(src.cols-100,100);
    dp[2] = cv::Point2f(src.cols-50,src.rows-50);

    cv::Mat m = cv::getAffineTransform(sp, dp);

    cv::Mat dst;
    cv::warpAffine(src, dst, m, cv::Size());

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void affineTranslation() {
    cv::Mat src = cv::imread("tekapo.bmp");
    if (!src.data) {
        return;
    }

    cv::Mat m = cv::Mat_<double>({2,3}, {1, 0, 150, 0, 1, 100});

    cv::Mat dst;
    cv::warpAffine(src, dst, m, cv::Size());

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void affineShear() {
    cv::Mat src = cv::imread("tekapo.bmp");
    if (!src.data) {
        return;
    }

    double mx = 0.3;
    cv::Mat m = cv::Mat_<double>({2,3}, {1, mx,0, 0, 1, 0});

    cv::Mat dst;
    cv::warpAffine(src, dst, m, cv::Size(cvRound(src.cols+src.rows*mx), src.rows));

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void affineScale() {
    cv::Mat src = cv::imread("tekapo.bmp");
    if (!src.data) {
        return;
    }

    cv::Mat d1, d2, d3, d4;
    cv::resize(src, d1, cv::Size(), 4, 4, cv::INTER_NEAREST);
    cv::resize(src, d2, cv::Size(1920, 1280));
    cv::resize(src, d3, cv::Size(1920, 1280), 0, 0, cv::INTER_CUBIC);
    cv::resize(src, d4, cv::Size(1920, 1280), 0, 0, cv::INTER_LANCZOS4);

    cv::imshow("src", src);
    cv::imshow("dst1", d1(cv::Rect(400, 500, 400, 400)));
    cv::imshow("dst2", d2(cv::Rect(400, 500, 400, 400)));
    cv::imshow("dst3", d3(cv::Rect(400, 500, 400, 400)));
    cv::imshow("dst4", d4(cv::Rect(400, 500, 400, 400)));

    cv::waitKey();
    cv::destroyAllWindows();
}

void affineRotation() {
    cv::Mat src = cv::imread("tekapo.bmp");
    if (!src.data) {
        return;
    }

    cv::Point2f cp(src.cols/2.f, src.rows/2.f);
    cv::Mat m = getRotationMatrix2D(cp, 20, 1);

    cv::Mat dst;
    cv::warpAffine(src, dst, m, cv::Size());

    cv::imshow("src", src);
    cv::imshow("dst", dst);

    cv::waitKey();
    cv::destroyAllWindows();
}

void affineFlip() {
    cv::Mat src = cv::imread("tekapo.bmp");
    if (!src.data) {
        return;
    }

    cv::Mat dst;

    cv::imshow("src", src);

    int flipCode[] = {1, 0, -1};
    for (int i=0; i<3; i++) {
        cv::flip(src, dst, flipCode[i]);

        std::string desc = cv::format("flipCode: %d", flipCode[i]);
        cv::putText(dst, desc, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 0, 0), 1, cv::LINE_AA);

        cv::imshow("dst", dst);
        cv::waitKey();
    }

    cv::destroyAllWindows();
}
