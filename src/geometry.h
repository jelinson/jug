#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <QDebug>
#include <opencv/cv.h>
#include "utils.h"
#include "globals.h"

#define SLOPE_DOMAIN 5

class NormalField;
typedef std::vector<cv::Point> Contour;

class Geometry
{
public:
    static NormalField countNormals(const Contour &contour, bool ccw=true);
    static void testNormals();

private:
    static cv::Point normal(const cv::Point &previous,
                            const cv::Point &next,
                            bool ccw);
};

class NormalField
{
public:
    NormalField();
    void add(const cv::Point &slope);
    int lookUp(const cv::Point &slope);

private:
    int _counts[SLOPE_DOMAIN][SLOPE_DOMAIN];

    friend QDebug operator<<(QDebug dbg, const NormalField &nf);
};

QDebug operator<<(QDebug dbg, const NormalField &nf);
QDebug operator<<(QDebug dbg, const cv::Point &p);

#endif // GEOMETRY_H
