#ifndef GRIP_H
#define GRIP_H

#include <vector>
#include <QDebug>
#include <opencv/cv.h>
#include "utils.h"
#include "globals.h"

class Grip
{
public:
    Grip(cv::Mat *img, std::vector<cv::Point> &contour);
    Grip(cv::Mat *img, std::vector<cv::Point> &contour, cv::Rect &boundingRect);

private:
    void analyze();

    cv::Mat *_img;
    std::vector<cv::Point> _contour;
    cv::Rect _boundingRect;
    cv::Point _com;
    cv::Moments _moments;
    std::vector<cv::Vec4i> _defects;
    int _area;
    int _perimeter; /// \todo colon initialize
};

#endif // GRIP_H
