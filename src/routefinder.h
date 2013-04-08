#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include <vector>
#include <QDebug>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "utils.h"
#include "globals.h"

class RouteFinder
{
public:
    RouteFinder();
    ~RouteFinder();
    void find(const std::string& imgPath, bool show=false);
    void showRoute(const std::string& imgPath);

private:
    void detectRoute();
    void splitHSV();

    bool _loaded;
    cv::Size _dim;
    cv::Mat _img;
    std::vector<cv::Mat> _hsv;
};

#endif // ROUTEFINDER_H
