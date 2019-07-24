#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::string;

void drawLines();
void drawPolys();
void drawText1();
void drawText2();

int main(void) {

    drawLines();
    drawPolys();
    drawText1();
    drawText2();

    return 0;
}

void drawLines() {
    cv::Mat canvas(400, 400, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::line(canvas, cv::Point(50, 50), cv::Point(200, 50), cv::Scalar(0, 0, 255));
    cv::line(canvas, cv::Point(50, 100), cv::Point(200, 100), cv::Scalar(255, 0, 255), 3);
    cv::line(canvas, cv::Point(50, 150), cv::Point(200, 150), cv::Scalar(255, 0, 0), 10);

    cv::line(canvas, cv::Point(250, 50), cv::Point(350, 100), cv::Scalar(0, 0, 255), 1, cv::LINE_4);
    cv::line(canvas, cv::Point(250, 70), cv::Point(350, 120), cv::Scalar(255, 0, 255), 1, cv::LINE_8);
    cv::line(canvas, cv::Point(250, 90), cv::Point(350, 140), cv::Scalar(255, 0, 0), 1, cv::LINE_AA);

    cv::arrowedLine(canvas, cv::Point(50, 200), cv::Point(150, 200), cv::Scalar(0, 0, 255), 1);
    cv::arrowedLine(canvas, cv::Point(50, 250), cv::Point(350, 250), cv::Scalar(255, 0, 255), 1);
    cv::arrowedLine(canvas, cv::Point(50, 300), cv::Point(350, 300), cv::Scalar(255, 0, 0), 1, cv::LINE_8, 0, 0.05);

    cv::drawMarker(canvas, cv::Point(50, 350), cv::Scalar(0, 0, 255), cv::MARKER_CROSS);
    cv::drawMarker(canvas, cv::Point(100, 350), cv::Scalar(0, 0, 255), cv::MARKER_TILTED_CROSS);
    cv::drawMarker(canvas, cv::Point(150, 350), cv::Scalar(0, 0, 255), cv::MARKER_STAR);
    cv::drawMarker(canvas, cv::Point(200, 350), cv::Scalar(0, 0, 255), cv::MARKER_DIAMOND);
    cv::drawMarker(canvas, cv::Point(250, 350), cv::Scalar(0, 0, 255), cv::MARKER_SQUARE);
    cv::drawMarker(canvas, cv::Point(300, 350), cv::Scalar(0, 0, 255), cv::MARKER_TRIANGLE_UP);
    cv::drawMarker(canvas, cv::Point(350, 350), cv::Scalar(0, 0, 255), cv::MARKER_TRIANGLE_DOWN);

    cv::imshow("canvas", canvas);
    cv::waitKey();
    cv::destroyAllWindows();
}

void drawPolys() {
    cv::Mat canvas(400, 400, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::rectangle(canvas, cv::Rect(50, 50, 100, 50), cv::Scalar(0, 0, 255), 2);
    cv::rectangle(canvas, cv::Rect(50, 150, 100, 50), cv::Scalar(0, 0, 128), -1);

    cv::circle(canvas, cv::Point(300, 120), 30, cv::Scalar(255, 255, 0), -1, cv::LINE_AA);
    cv::circle(canvas, cv::Point(300, 120), 60, cv::Scalar(255, 0, 0), 3, cv::LINE_AA);

    cv::ellipse(canvas, cv::Point(120, 300), cv::Size(60, 30), 20, 0, 270, cv::Scalar(255, 255, 0), cv::FILLED, cv::LINE_AA);
    cv::ellipse(canvas, cv::Point(120, 300), cv::Size(100, 50), 20, 0, 360, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);

    vector<cv::Point> pts;
    pts.push_back(cv::Point(250, 250));
    pts.push_back(cv::Point(300, 250));
    pts.push_back(cv::Point(300, 300));
    pts.push_back(cv::Point(350, 300));
    pts.push_back(cv::Point(350, 350));
    pts.push_back(cv::Point(250, 350));
    cv::polylines(canvas, pts, true, cv::Scalar(255, 0, 255), 2);

    cv::imshow("canvas", canvas);
    cv::waitKey();
    cv::destroyAllWindows();
}

void drawText1() {
    cv::Mat canvas(500, 800, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::putText(canvas, "simplex", cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255));
    cv::putText(canvas, "plain", cv::Point(20, 100), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255));
    cv::putText(canvas, "duplex", cv::Point(20, 150), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 255));
    cv::putText(canvas, "complex", cv::Point(20, 200), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 0, 0));
    cv::putText(canvas, "triplex", cv::Point(20, 250), cv::FONT_HERSHEY_TRIPLEX, 1, cv::Scalar(255, 0, 0));
    cv::putText(canvas, "complex small", cv::Point(20, 300), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(255, 0, 0));
    cv::putText(canvas, "script simplex", cv::Point(20, 350), cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 1, cv::Scalar(255, 0, 0));
    cv::putText(canvas, "script complex", cv::Point(20, 400), cv::FONT_HERSHEY_SCRIPT_COMPLEX, 1, cv::Scalar(255, 0, 0));
    cv::putText(canvas, "complex | italic", cv::Point(20, 450), cv::FONT_HERSHEY_COMPLEX | cv::FONT_ITALIC, 1, cv::Scalar(255, 0, 0));

    cv::imshow("canvas", canvas);
    cv::waitKey();
    cv::destroyAllWindows();
}

void drawText2() {
    cv::Mat canvas(200, 640, CV_8UC3, cv::Scalar(255, 255, 255));

    const string text = "Hello, OpenCV";
    int fontFace = cv::FONT_HERSHEY_TRIPLEX;
    double fontScale = 2.0;
    int thickness = 1;

    cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, 0);
    cv::Size imgSize = canvas.size();

    cv::Point org((imgSize.width - textSize.width) / 2, (imgSize.height + textSize.height) / 2);
    cv::putText(canvas, text, org, fontFace, fontScale, cv::Scalar(255, 0, 0), thickness);
    cv::rectangle(canvas, org, org + cv::Point(textSize.width, -textSize.height), cv::Scalar(0, 255, 0), 1);

    cv::imshow("canvas", canvas);
    cv::waitKey();
    cv::destroyAllWindows();
}
