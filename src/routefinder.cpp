#include "routefinder.h"

using namespace cv;

RouteFinder::RouteFinder()
    : _loaded(false)
{
    _blobParams.blobColor = 155;
    _blobParams.minArea = 300;
    _blobParams.minConvexity = 0;
    _blob = new SimpleBlobDetector(_blobParams);
}

RouteFinder::~RouteFinder()
{
    delete _blob;
}

void RouteFinder::find(std::string imgPath)
{
    _path = imgPath;
    _img = imread(_path, CV_LOAD_IMAGE_COLOR);
    if (!_img.data) {
        qDebug() << "Could not load" << _path.c_str();
        _loaded = false;
    }

    if (_img.cols > _img.rows)
        _img = _img.t();

    detectRoute();
}

void RouteFinder::showRoute()
{
    for (int i = 0; i < _pts.size(); ++i)
        circle(_img, _pts[i].pt, _pts[i].size/2, CV_RGB(255, 255, 255));

    cv::Mat toShow(_img.clone());

    resize(_img, toShow, Size(408, 508));
    imshow(_path, toShow);
    waitKey(0);
}

void RouteFinder::detectRoute()
{
    _blob->detect(_img, _pts);
    qDebug() << "Found" << _pts.size() << "blobs";
}
