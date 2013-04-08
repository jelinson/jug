#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include <vector>
#include <QDebug>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "globals.h"

class RouteFinder
{
public:
    RouteFinder();
    ~RouteFinder();
    void find(std::string& imgPath, bool show=false);
    void showRoute(std::string& imgPath);

private:
    void detectRoute();

    bool _loaded;
    cv::Size _dim;
    cv::Mat _img;
    std::vector<cv::KeyPoint> _pts;
};

#endif // ROUTEFINDER_H
