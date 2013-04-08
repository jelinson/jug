#include "utils.h"

namespace jug {

static int x = 0;

void showImage(const cv::Mat* img, const std::string& title, bool wait)
{
    cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
    cv::imshow(title, *img);
    cv::moveWindow(title, x, 0);
    x += img->cols + 4;
    if (wait) {
        cv::waitKey();
        x = 0;
    }
}

}
