#ifndef PHYSICS_H
#define PHYSICS_H

#include <QList>
#include <opencv/cv.h>
#include "climberstate.h"
#include "climberspecs.h"
#include "route.h"
#include "globals.h"

class Physics
{
public:
    Physics();
    bool isPossible(const ClimberState& pos) const;
    QList<ClimberState> configurations(const ClimberState& pos) const;
    void loadClimber(const ClimberSpecs &specs);
    void loadRoute(const Route* r);
    bool isRouteLoaded() const;
    void fillInCom(ClimberState &state, cv::Point com=cv::Point(-1, -1)) const;
    bool isReachableStart(const ClimberState& pos);

private:
    const Route* _route;
    ClimberSpecs _specs;
};

#endif // PHYSICS_H
