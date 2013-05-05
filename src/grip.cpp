#include "grip.h"

using namespace std;
using namespace cv;

Grip::Grip(const Contour &contour)
    : _contour(contour), _area(-1), _perimeter(-1)
{
    _boundingRect = minAreaRect(_contour).boundingRect();
}

Grip::Grip(const Contour &contour, const Rect &boundingRect)
    : _contour(contour),
      _boundingRect(boundingRect),
      _area(-1),
      _perimeter(-1)
{
    // Nothing to do
}

bool Grip::handHold() const
{
    return (_perimeter >= MIN_HAND_HOLD_PERIMETER) &&
            (abs(_area) >= MIN_HAND_HOLD_AREA);
}

bool Grip::nLimbs(int i) const
{
    return _perimeter >= i * MIN_PERIMETER_PER_LIMB;
}

bool Grip::ptrComp(const Grip *a, const Grip *b)
{
    return *a < *b;
}

bool Grip::analyze()
{
    _moments = moments(_contour);
    _area = contourArea(_contour, true);
    _com = Point(_moments.m10/abs(_area), _moments.m01/abs(_area));
    _perimeter = arcLength(_contour, true);

    vector<int> hull;
    convexHull(_contour, hull);
    if (hull.size() > 3)
        convexityDefects(_contour, hull, _defects);

    if (_com.x >= 0 && _com.y >= 0)
        _nf = Geometry::countNormals(_contour, _area < 0);

    // false means invalid
    return _area != 0;
}

QDebug operator<<(QDebug d, const Grip &g)
{
    d.nospace() << "Grip: (x: "
                << g._com.x << ", y: "
                << g._com.y << ", area: "
                << g._area << ", perm: "
                << g._perimeter << ", ndef: "
                << g._defects.size()
                << ")";
    qDebug() << g._nf;
    return d.space();
}

bool operator<(const Grip& a, const Grip& b)
{
    // smaller y values coresponds to higher in image and hence high in route
    return a.getCom().y > b.getCom().y;
}
