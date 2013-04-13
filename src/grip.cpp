#include "grip.h"

using namespace std;
using namespace cv;

Grip::Grip(Mat *img, vector<Point> &contour)
    : _img(img),
      _contour(contour)
{
    _boundingRect = minAreaRect(_contour).boundingRect();
    analyze();
}

Grip::Grip(Mat *img, vector<Point> &contour, Rect &boundingRect)
    : _img(img),
      _contour(contour),
      _boundingRect(boundingRect)
{
    analyze();
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


