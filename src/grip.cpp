#include "grip.h"

using namespace std;
using namespace cv;

Grip::Grip(const Contour &contour)
    : _contour(contour)
{
    _boundingRect = minAreaRect(_contour).boundingRect();
}

Grip::Grip(const Contour &contour, const Rect &boundingRect)
    : _contour(contour),
      _boundingRect(boundingRect)
{
    // Nothing to do
}

void Grip::analyze()
{
    _moments = moments(_contour);
    _area = contourArea(_contour);
    _com = Point(_moments.m10/_area, _moments.m01/_area);
    _perimeter = arcLength(_contour, true);

    vector<int> hull;
    convexHull(_contour, hull);
    if (hull.size() > 3)
        convexityDefects(_contour, hull, _defects);
}

QDebug operator<<(QDebug d, const Grip &g)
{
    d.nospace() << "Grip: (x: "
                << g._com.x << ", y: "
                << g._com.y << ", area: "
                << g._area << ", perm: "
                << g._perimeter << ", ndef: "
                << g._defects.size();
    return d.space();
}
