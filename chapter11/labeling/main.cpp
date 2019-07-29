#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

void labelingBasic();
void labelingStats();

int main(void) {
    labelingBasic();
    labelingStats();

    return 0;
}

void labelingBasic() {
    uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

    cv::Mat src = cv::Mat(8, 8, CV_8U, data) * 255;

    cv::Mat labels;
    int cnt = cv::connectedComponents(src, labels);

    cout << "src: \n" << src << "\n\n";
    cout << "labels: \n" << labels << "\n\n";
    cout << "number of labels: \n" << cnt << "\n\n";
}

void labelingStats() {
    cv::Mat src = cv::imread("./keyboard.bmp", 0);
    if (!src.data) {
        return;
    }

    cv::Mat bin;
    cv::threshold(src, bin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Mat labels, stats, centroids;
    int cnt = cv::connectedComponentsWithStats(bin, labels, stats, centroids);

    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);

    for (int i=0; i<cnt; i++) {
        int *p = stats.ptr<int>(i);
        if (p[4] < 20) {
            continue;
        }

        cv::rectangle(dst, cv::Rect(p[0], p[1], p[2], p[3]), cv::Scalar(0, 255, 255));
    }

    cv::imshow("src", src);
    cv::imshow("dst", dst);
    cv::imshow("bin", bin);

    cv::waitKey();
    cv::destroyAllWindows();
}
