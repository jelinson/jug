#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "globals.h"

namespace jug {
    void showImage(const cv::Mat* img, const std::string& title, bool wait=false);
    bool loadImage(const std::string& path, cv::Mat& dst);
    bool validPoint(const cv::Point& pos);
}

#endif // UTILS_H
