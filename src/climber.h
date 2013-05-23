#ifndef CLIMBER_H
#define CLIMBER_H

#include "stdio.h"
#include <opencv/cv.h>
#include <QList>
#include "climberspecs.h"
#include "pathproblem.h"
#include "physics.h"
#include "route.h"
#include "searcher.h"
#include "utils.h"
#include "globals.h"

class Climber
{
public:
    Climber(Physics *engine, const ClimberSpecs& specs);
    void setSpecs(const ClimberSpecs& specs);
    void setEngine(Physics *engine);

    /// \todo multiple solution route option
    Path climb(const Route& r, bool visualize=true) const;

private:
    QList<ClimberState> start(const Route& r) const;
    void visualizePath(const Route& r, const Path& p) const;
    void visualizeState(const Route& r, const ClimberState& pos, int index=-1) const;
    void drawState(cv::Mat& img, const Route &r, const ClimberState s) const;

    Physics *_engine;
    ClimberSpecs _specs;

    static const QList<cv::Scalar> limbColors;
};

#endif // CLIMBER_H
