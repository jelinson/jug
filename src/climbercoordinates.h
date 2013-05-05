#ifndef CLIMBERCOORDINATES_H
#define CLIMBERCOORDINATES_H

#include <opencv/cv.h>
#include <QList>
#include "climberstate.h"
#include "grip.h"
#include "route.h"

/// \todo rename since it stores more than com coordinates now
class ClimberCoordinates
{
public:
    ClimberCoordinates(const ClimberState& state, const Route* route);
    const Grip* getGrip(int i) const;
    const Grip* getGrip(Limb i) const;
    cv::Point operator[](int i) const;
    cv::Point operator[](Limb i) const;

private:
    QList<cv::Point> _pos;
    QList<const Grip*> _grips;
};

#endif // CLIMBERCOORDINATES_H
