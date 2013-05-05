#include "utils.h"

namespace jug {

static int x = 0;

void showImage(const cv::Mat* img, const std::string& title, bool wait)
{
    Q_ASSERT(img->data);
    cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
    cv::imshow(title, *img);
    cv::moveWindow(title, x, 0);
    x += img->cols + 4;
    if (wait) {
        cv::waitKey();
        x = 0;
    }
}

bool loadImage(const std::string& path, cv::Mat& dst)
{
    cv::Mat img = cv::imread(path, CV_LOAD_IMAGE_COLOR);
    if (img.cols > img.rows)
        img = img.t();

    if (!img.data) {
        qDebug() << "Could not load" << path.c_str();
        return false;
    }

    cv::resize(img, dst, cv::Size(IMG_WIDTH, IMG_HEIGHT));
    if (!dst.data) {
        qDebug() << "Could not resize" << path.c_str();
        return false;
    }
    return true;
}

void clearImages()
{
    cv::destroyAllWindows();
    x = 0;
}

bool validPoint(const cv::Point& pos)
{
    return pos.x >= 0 && pos.y >= 0 && pos.x < IMG_WIDTH && pos.y < IMG_HEIGHT;
}

int fromGround(int y)
{
    return IMG_HEIGHT - y;
}

}
