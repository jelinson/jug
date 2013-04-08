#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace jug {
    void showImage(const cv::Mat* img, const std::string& title, bool wait=false);
}

#endif // UTILS_H
