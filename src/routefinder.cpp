#include "routefinder.h"

using namespace cv;

static int xMouse = 0;
static int yMouse = 0;

static void mouseEvent(int event, int x, int y, int, void*)
{
    if (event == CV_EVENT_LBUTTONDOWN) {
        xMouse = x;
        yMouse = y;
    }
}

RouteFinder::RouteFinder()
    : _loaded(false),
      _routeHue(0),
      _dim(IMG_WIDTH, IMG_HEIGHT),
      _minSatThres(MIN_SAT_THRES),
      _maxSatThres(MAX_SAT_THRES)
{
    // Nothing to do
}

RouteFinder::~RouteFinder()
{
    // Nothing to do yet
}

void RouteFinder::find(const std::string& imgPath, bool show)
{
    _routeHue = 0;
    Mat img = imread(imgPath, CV_LOAD_IMAGE_COLOR);
    if (img.cols > img.rows)
        img = img.t();

    if (!img.data) {
        qDebug() << "Could not load" << imgPath.c_str();
        _loaded = false;
        return;
    }

    _img = Mat();
    resize(img, _img, _dim);

    if (_img.data)
        _loaded = true;
    else {
        qDebug() << "Could not resize image";
        _loaded = false;
        return;
    }

    detectRoute();
    if (show)
        showRoute(imgPath);
}

void RouteFinder::showRoute(const std::string &imgPath)
{
    jug::showImage(&_img, imgPath, true);
}

void RouteFinder::splitHSV()
{
    Mat hsvImg;
    cvtColor(_img, hsvImg, CV_BGR2HSV);
    split(hsvImg, _hsvChannels);
}

void RouteFinder::getRouteHue()
{
    xMouse = -1;
    yMouse = -1;
    jug::showImage(&_img, "Select a route");
    setMouseCallback("Select a route", mouseEvent, 0);
    while (xMouse < 0)
        waitKey(30);
    _routeHue = _hsvChannels[0].data[yMouse * _hsvChannels[0].cols + xMouse];
    qDebug() << "Searching for route with hue" << _routeHue;
}

void RouteFinder::denoise()
{
    dilate(_routeMask, _routeMask, Mat(), Point(-1,-1), 2);
    erode(_routeMask, _routeMask, Mat(), Point(-1, -1), 3);
    dilate(_routeMask, _routeMask, Mat(), Point(-1,-1), 1);
}

void RouteFinder::detectRoute()
{
    splitHSV();
    getRouteHue();

    Mat hueMask, satMask;
    inRange(_hsvChannels[0], Scalar(_routeHue - HUE_MARGIN), Scalar(_routeHue + HUE_MARGIN), hueMask);
    inRange(_hsvChannels[1], _minSatThres, _maxSatThres, satMask);

    bitwise_and(hueMask, satMask, _routeMask);
    denoise();
    jug::showImage(&_routeMask, "Route");

    /// \todo for each blob, check mean rgb and proxity to given input
    /// \todo look for nested contours with hierarchy argument
    vector<vector<Point> > contours;
    findContours(_routeMask, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    Mat drawing = Mat::zeros(_routeMask.size(), CV_8UC1);
    for (int i = 0; i < contours.size(); ++i) {
        drawContours(drawing, contours, i, Scalar(255), 2, 8);
    }
    qDebug() << "Found" << contours.size() << "contours";
    jug::showImage(&drawing, "Contours", true);
}

