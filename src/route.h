#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <iostream>
#include "algorithm"
#include <opencv/cv.h>
#include "grip.h"
#include "utils.h"
#include "globals.h"

class Route
{
public:
    Route(cv::Mat *img);
    ~Route();
    void loadFromContours(const std::vector<Contour> &contours);
    void analyzeGrips();
    void visualize();
    cv::Mat imgCopy() const;
    int nGrips() const;
    int lastGrip() const;
    const Grip* operator[](int i) const;

private:
    cv::Mat *_img;
    std::vector<Grip*> _grips;
};

#endif // ROUTE_H
