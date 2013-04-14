#include "geometry.h"

using namespace std;
using namespace cv;

NormalField Geometry::countNormals(const Contour &contour, bool ccw)
{
    int lastIndex = contour.size() - 1;
    NormalField nf;
    for (int i = 1; i < lastIndex; ++i)
        nf.add(normal(contour[i-1], contour[i+1], ccw));

    // wrap around
    nf.add(normal(contour[lastIndex], contour[1], ccw));
    nf.add(normal(contour[lastIndex - 1], contour[0], ccw));
    return nf;
}

Point Geometry::normal(const Point &previous, const Point &next, bool ccw)
{
    Point diff = next - previous;
    Point normal(diff.y, -(diff.x));
    if (ccw)
        return normal;
    else
        return -1*normal;
}

NormalField::NormalField()
{
    for (int x = 0; x < SLOPE_DOMAIN; ++x)
        for (int y = 0; y < SLOPE_DOMAIN; ++y)
            _counts[x][y] = 0;
}

void NormalField::add(const Point &slope)
{
    int offset = SLOPE_DOMAIN / 2;
    Q_ASSERT(slope.x+offset >= 0 && slope.x+offset < SLOPE_DOMAIN);
    Q_ASSERT(slope.y+offset >= 0 && slope.y+offset < SLOPE_DOMAIN);

    ++_counts[slope.x+offset][slope.y+offset];
}

int NormalField::lookUp(const Point &slope)
{
    return _counts[slope.x][slope.y];
}

QDebug operator<<(QDebug dbg, const NormalField &nf)
{
    dbg.nospace() << "      x    \n";
    dbg.nospace() << "-2 -1  0  1  2\n";
    for (int x = 0; x < SLOPE_DOMAIN; ++x) {
        for (int y = 0; y < SLOPE_DOMAIN; ++y)
            dbg.space() << nf._counts[x][y];
        dbg.nospace() << "\n";
    }
    return dbg.space();
}

QDebug operator<<(QDebug dbg, const cv::Point &p)
{
    dbg.nospace() << "(" << p.x << ", " << p.y << ")";
    return dbg.space();
}
