#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "route.h"
#include "grip.h"
#include "utils.h"
#include "globals.h"

class RouteFinder
{
public:
    RouteFinder();
    ~RouteFinder();
    Route find(cv::Mat *img);

private:
    void splitHSV();
    void getRouteHue();
    void denoise();
    void colorFilter();

    bool _loaded;
    int _routeHue;
    int _routeXSelection, _routeYSelection;
    cv::Scalar _minSatThres, _maxSatThres;
    cv::Mat* _img;
    cv::Mat _routeMask;
    std::vector<cv::Mat> _hsvChannels;
};

#endif // ROUTEFINDER_H
