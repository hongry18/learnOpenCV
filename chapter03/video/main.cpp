#include <iostream>
#include "opencv2/opencv.hpp"

void cameraIn();
void videoIn();
void cameraInVideoOut();

int main(void) {
    cameraIn();
    videoIn();
    cameraInVideoOut();

    return 0;
}

void cameraIn() {
    cv::VideoCapture cap(1);
    if (!cap.isOpened()) {
        return;
    }

    cv::Mat f, inv;

    while(1) {
        cap.read(f);
        if (!f.data) {
            break;
        }

        inv = ~f;

        cv::imshow("f", f);
        cv::imshow("inv", inv);

        if (cv::waitKey() == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
}

void videoIn() {
    cv::VideoCapture cap("output.avi");

    if (!cap.isOpened()) {
        return;
    }

    cv::Mat f, inv;

    double fps = cap.get(cv::CAP_PROP_FPS);
    int delay = cvRound(1000/fps);

    while(1) {
        cap.read(f);
        if (!f.data) {
            break;
        }

        inv = ~f;

        cv::imshow("f", f);
        cv::imshow("inv", inv);

        if (cv::waitKey() == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
}

void cameraInVideoOut() {
    cv::VideoCapture cap(1);

    if (!cap.isOpened()) {
        printf("camera not opened\n");
        return;
    }
    cv::Mat f, inv;

    int w = cvRound(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int h = cvRound(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    double fps = cap.get(cv::CAP_PROP_FPS);
    int fourcc = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    int delay = cvRound(1000/fps);

    cv::VideoWriter writer("./output.avi", fourcc, fps, cv::Size(w, h), true);

    if (!writer.isOpened()) {
        printf("fileNotOpen\n");
        return;
    }

    while(1) {
        cap.read(f);
        if (!f.data) {
            break;
        }

        inv = ~f;
        writer << inv;

        cv::imshow("f", f);
        cv::imshow("inv", inv);

        if (cv::waitKey() == 27) {
            break;
        }
    }

    cap.release();
    writer.release();
    cv::destroyAllWindows();
}
