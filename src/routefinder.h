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
    void getRouteHue();
    void denoise();
    void colorFilter();

    bool _loaded;
    int _routeHue;
    int _routeXSelection, _routeYSelection;
    cv::Size _dim;
    cv::Scalar _minSatThres, _maxSatThres;
    cv::Mat _img;
    cv::Mat _routeMask;
    std::vector<cv::Mat> _hsvChannels;
};

#endif // ROUTEFINDER_H
