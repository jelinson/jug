#ifndef GRIP_H
#define GRIP_H

#include <vector>
#include <QDebug>
#include <opencv/cv.h>
#include "geometry.h"
#include "utils.h"
#include "globals.h"

typedef std::vector<cv::Point> Contour;

class Grip
{
public:
    Grip(const Contour &contour);
    Grip(const Contour &contour, const cv::Rect &boundingRect);
    inline Contour getContour() const
    {
        return _contour;
    }

private:
    void analyze();

    Contour _contour;
    cv::Rect _boundingRect;
    cv::Point _com;
    cv::Moments _moments;
    std::vector<cv::Vec4i> _defects;
    NormalField _nf;
    double _area;
    int _perimeter; /// \todo colon initialize

    friend class Route;
    friend QDebug operator<<(QDebug, const Grip&);
};

QDebug operator<<(QDebug d, const Grip &g);

#endif // GRIP_H
