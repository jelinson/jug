#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include <vector>
#include <QString>
#include <QDebug>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>

class RouteFinder
{
public:
    RouteFinder();
    ~RouteFinder();
    void find(std::string imgPath);
    void showRoute();

private:
    void detectRoute();

    bool _loaded;
    cv::Mat _img;
    std::vector<cv::KeyPoint> _pts;
    std::string _path;
    cv::SimpleBlobDetector* _blob;
    cv::SimpleBlobDetector::Params _blobParams;
};

#endif // ROUTEFINDER_H
