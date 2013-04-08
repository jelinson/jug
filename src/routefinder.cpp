#include "routefinder.h"

using namespace cv;

RouteFinder::RouteFinder()
    : _loaded(false),
      _dim(IMG_WIDTH, IMG_HEIGHT)
{
    // Nothing to do
}

RouteFinder::~RouteFinder()
{
    // Nothing to do yet
}

void RouteFinder::find(const std::string& imgPath, bool show)
{
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
    imshow(imgPath, _img);
    waitKey(0);
}

void mouseEvent(int event, int x, int y, int flags, void* param)
{
    if (event == CV_EVENT_LBUTTONDOWN) {
        Mat* hue = (Mat*) param;
        int value = hue->data[y*hue->cols + x];
        qDebug() << value;
    }
}

void RouteFinder::detectRoute()
{
    Mat hsv;
    cvtColor(_img, hsv, CV_BGR2HSV);
    vector<Mat> channels(3);
    split(hsv, channels);
    jug::showImage(&_img, "orig");
    jug::showImage(&channels[0], "hue");
    //namedWindow("orig", WINDOW_AUTOSIZE);
    //imshow("orig", _img);
    //namedWindow("hue", WINDOW_AUTOSIZE);
    //imshow("hue", channels[0]);
    //namedWindow("s", WINDOW_AUTOSIZE);
    //imshow("s", channels[1]);

    Mat binaryHue;
    //inRange(channels[0], Scalar(78), Scalar(90), binaryHue);
    inRange(channels[0], Scalar(170), Scalar(184), binaryHue);
    //inRange(channels[0], Scalar(98), Scalar(108), binaryHue);
    //namedWindow("bin", WINDOW_AUTOSIZE);
    //imshow("bin", binaryHue);

    /// \todo normalize values perhaps on a per image basis
    Mat binarySat;
    inRange(channels[1], Scalar(40), Scalar(255), binarySat);
    //namedWindow("binSay", WINDOW_AUTOSIZE);
    //imshow("binSay", binarySat);

    Mat route;
    bitwise_and(binaryHue, binarySat, route);
    //namedWindow("route", WINDOW_AUTOSIZE);
    //imshow("route", route);

    setMouseCallback("hue",mouseEvent, &channels[0]);
    setMouseCallback("s",mouseEvent, &channels[1]);
    setMouseCallback("v",mouseEvent, &channels[2]);

    Mat denoised;
    //erode(route, denoised, Mat());
    dilate(route, denoised, Mat(), Point(-1,-1), 2);
    erode(denoised, denoised, Mat(), Point(-1, -1), 3);
    dilate(denoised, denoised, Mat(), Point(-1,-1), 1);
    //namedWindow("quiet", WINDOW_AUTOSIZE);
    //imshow("quiet", denoised);

    /// \todo for each blob, check mean rgb and proxity to given input
    /// \todo look for nested contours with hierarchy argument
    vector<vector<Point> > contours;
    findContours(denoised, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    Mat drawing = Mat::zeros(route.size(), CV_8UC1);
    for (int i = 0; i < contours.size(); ++i) {
        drawContours(drawing, contours, i, Scalar(255), 2, 8);
    }
    qDebug() << "Found" << contours.size() << "contours";

    //namedWindow("cont", WINDOW_AUTOSIZE);
    //imshow("cont", drawing);
    waitKey();
}

