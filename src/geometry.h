#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "math.h"
#include <vector>
#include <opencv/cv.h>
#include <QMap>
#include <QPair>
#include "utils.h"
#include "globals.h"

#define PI 3.14159265

class NormalField;
typedef std::vector<cv::Point> Contour;

class Geometry
{
public:
    static NormalField countNormals(const Contour &contour, bool ccw=true);
    static void testNormals();

    static cv::Point discreteSlope(const cv::Point& src, const cv::Point& dst);
    static cv::Point lookUpSlope(double theta);
    static double wrapTo2Pi(double theta);

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
    int lookUp(const cv::Point &slope) const;

private:
    int _counts[SLOPE_RANGE][SLOPE_RANGE];
    static const int _offset;

    friend QDebug operator<<(QDebug dbg, const NormalField &nf);
};

QDebug operator<<(QDebug dbg, const NormalField &nf);
QDebug operator<<(QDebug dbg, const cv::Point &p);

#endif // GEOMETRY_H
