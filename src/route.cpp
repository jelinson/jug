#include "route.h"

using namespace std;
using namespace cv;

Route::Route(Mat *img)
    : _img(img)
{
    // Nothing to do
}

void Route::loadFromContours(const std::vector<Contour> &contours)
{
    _grips.reserve(contours.size());

    for (int i = 0; i < contours.size(); ++i) {
        Grip g(contours[i]);
        _grips.push_back(g);
    }
}

void Route::analyzeGrips()
{
    for (int i = 0; i < _grips.size(); ++i)
        _grips[i].analyze();
}
