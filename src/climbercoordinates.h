#ifndef CLIMBERCOORDINATES_H
#define CLIMBERCOORDINATES_H

#include <opencv/cv.h>
#include <QList>
#include "climberstate.h"
#include "route.h"

class ClimberCoordinates
{
public:
    ClimberCoordinates(const ClimberState& state, const Route* route);
    QList<cv::Point> _pos;
    cv::Point operator[](int i) const;
};

#endif // CLIMBERCOORDINATES_H
