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
}

void Route::analyzeGrips()
{
    for (int i = 0; i < _grips.size(); ++i)
        _grips[i]->analyze();

    sort(_grips.begin(), _grips.end());
}

void Route::visualize()
{
    for (int i = 0; i < _grips.size(); ++i) {
        Mat gripViewer = imgCopy();
        Q_ASSERT(gripViewer.data);

        vector<Contour> contourWrapper(1, _grips[i]->getContour());
        drawContours(gripViewer, contourWrapper, 0, Scalar(255), 2);

        qDebug() << *(_grips[i]);
        jug::showImage(&gripViewer, "Route", true);
    }
}

Mat Route::imgCopy() const
{
    Mat copy = _img->clone();
    if (!copy.data)
        qFatal("Could not clone matrix");
    return copy;
}

int Route::nGrips() const
{
    return _grips.size();
}

int Route::lastGrip() const
{
    Q_ASSERT(_grips.size() != 0);
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
