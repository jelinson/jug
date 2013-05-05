#ifndef GRIP_H
#define GRIP_H

#include <vector>
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
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

    inline cv::Point getCom() const
    {
        return _com;
    }

    bool handHold() const;
    bool nLimbs(int i) const;

    static bool ptrComp(const Grip* a, const Grip* b);

private:
    bool analyze();

    Contour _contour;
    cv::Rect _boundingRect;
    cv::Point _com;
    cv::Moments _moments;
    std::vector<cv::Vec4i> _defects;
    NormalField _nf;
    double _area;
    int _perimeter;

    friend class Route;
    friend class Physics;
    friend QDebug operator<<(QDebug, const Grip&);
};

QDebug operator<<(QDebug d, const Grip &g);
bool operator<(const Grip& a, const Grip& b);

#endif // GRIP_H
