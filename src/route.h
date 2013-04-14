#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <iostream>
#include <QDebug>
#include <opencv/cv.h>
#include "grip.h"
#include "utils.h"
#include "globals.h"

class Route
{
public:
    Route(cv::Mat *img);
    void loadFromContours(const std::vector<Contour> &contours);
    void analyzeGrips();
    void visualize();

private:
    cv::Mat *_img;
    std::vector<Grip> _grips;
};

#endif // ROUTE_H
