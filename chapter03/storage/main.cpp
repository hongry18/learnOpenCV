#include <iostream>
#include "opencv2/opencv.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void writeData();
void readData();

string fname = "mydata.json";

int main(void) {
    writeData();
    readData();

    return 0;
}

void writeData() {
    string name = "Jain";
    int age = 10;
    cv::Point p(100, 200);
    vector<int> s = { 80, 90, 50 };
    cv::Mat m = (cv::Mat_<float>(2,2) << 1.f, 1.5f, 2.f, 2.5f);

    cv::FileStorage fs;
    fs.open(fname, cv::FileStorage::WRITE);

    if (!fs.isOpened()) {
        cout << "file open failed: " << fname << endl;
        return;
    }

    fs << "name" << name;
    fs << "age" << age;
    fs << "point" << p;
    fs << "sources" << s;
    fs << "data" << m;

    fs.release();
}

void readData() {
    string name;
    int age;
    cv::Point p;
    vector<int> s;
    cv::Mat m;

    cv::FileStorage fs(fname, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        cout << "file open failed: " << fname << endl;
        return;
    }

    fs["name"] >> name;
    fs["age"] >> age;
    fs["point"] >> p;
    fs["sources"] >> s;
    fs["data"] >> m;

    fs.release();

    cout << "name: " << name << "\n";
    cout << "age: " << age << "\n";
    cout << "point: " << p << "\n";
    cout << "source: " << cv::Mat(s).t() << "\n";
    cout << "mat Data: " << m << endl;
}
