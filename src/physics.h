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
    void loadClimber(const ClimberSpecs& specs);
    void loadRoute(const Route* r);
    void fillInCom(ClimberState &state, cv::Point com=cv::Point(-1, -1)) const;
    bool isReachableStart(const ClimberState& current);

private:
    const Route* _route;
};

#endif // PHYSICS_H
