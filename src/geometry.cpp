#include "geometry.h"

using namespace std;
using namespace cv;

const int NormalField::_offset = SLOPE_RANGE / 2;

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

/*
 * 90 degree rotation of slope (270 if !ccw)
 */
Point Geometry::normal(const Point &previous, const Point &next, bool ccw)
{
    Point diff = next - previous;
    Point normal(-diff.y, diff.x);
    if (ccw)
        return normal;
    else
        return -1*normal;
}

NormalField::NormalField()
{
    for (int x = 0; x < SLOPE_RANGE; ++x)
        for (int y = 0; y < SLOPE_RANGE; ++y)
            _counts[x][y] = 0;
}

void NormalField::add(const Point &slope)
{
    Q_ASSERT(slope.x + _offset >= 0 && slope.x + _offset < SLOPE_RANGE);
    Q_ASSERT(slope.y + _offset >= 0 && slope.y + _offset < SLOPE_RANGE);

    ++_counts[slope.x + _offset][slope.y + _offset];
}

int NormalField::lookUp(const Point &slope)
{
    return _counts[slope.x][slope.y];
}

void Geometry::testNormals()
{
    Contour square;
    square.push_back(Point(0,0));
    square.push_back(Point(0,1));
    square.push_back(Point(0,2));
    square.push_back(Point(0,3));
    square.push_back(Point(1,3));
    square.push_back(Point(1,2));
    square.push_back(Point(1,1));
    square.push_back(Point(1,0));
    qDebug() << "Square\n" << countNormals(square);

    Contour hexagon;
    hexagon.push_back(Point(0,0));
    hexagon.push_back(Point(0,1));
    hexagon.push_back(Point(1,2));
    hexagon.push_back(Point(2,2));
    hexagon.push_back(Point(3,1));
    hexagon.push_back(Point(3,0));
    hexagon.push_back(Point(2,0));
    hexagon.push_back(Point(1,0));
    qDebug() << "Hexagon\n" << countNormals(hexagon);
}

QDebug operator<<(QDebug dbg, const NormalField &nf)
{
    dbg.nospace() << "         x    \n";
    dbg.nospace() << "   -2 -1  0  1  2\n";
    dbg.nospace() << "   --------------\n";
    for (int y = 0; y < SLOPE_RANGE; ++y) {
        dbg.nospace() << qPrintable(QString::number(y - nf._offset).rightJustified(2))
                      << "|";
        for (int x = 0; x < SLOPE_RANGE; ++x)
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
