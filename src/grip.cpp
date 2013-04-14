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
    _com = Point(_moments.m01/_area, _moments.m10/_area);
    _perimeter = arcLength(_contour, true);

    vector<int> hull;
    convexHull(_contour, hull);
    convexityDefects(_contour, hull, _defects);
}


