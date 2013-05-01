#include "route.h"

using namespace std;
using namespace cv;

Route::Route(Mat *img)
    : _img(img)
{
    // Nothing to do
}

Route::~Route()
{
    for (int i = 0; i < _grips.size(); ++i)
        delete _grips[i];
}

void Route::loadFromContours(const vector<Contour> &contours)
{
    _grips.reserve(contours.size());

    for (int i = 0; i < contours.size(); ++i)
        _grips.push_back(new Grip(contours[i]));

    sort(_grips.begin(), _grips.end());
}

void Route::analyzeGrips()
{
    for (int i = 0; i < _grips.size(); ++i)
        _grips[i]->analyze();
}

void Route::visualize()
{
    for (int i = 0; i < _grips.size(); ++i) {
        Mat gripViewer = _img->clone();
        if (!gripViewer.data) {
            qFatal("Could not clone matrix");
            continue;
        }

        vector<Contour> contourWrapper(1, _grips[i]->getContour());
        drawContours(gripViewer, contourWrapper, 0, Scalar(255), 2, 8);
        qDebug() << *(_grips[i]);
        jug::showImage(&gripViewer, "Route", true);
    }
}

int Route::nGrips()
{
    return _grips.size();
}

int Route::lastGrip()
{
    return _grips.size() - 1;
}

const Grip *Route::operator [](int i) const
{
    if (i >= 0)
        return _grips[i];
    else {
        qDebug() << "Smudging look-up";
        return NULL;
    }
}
