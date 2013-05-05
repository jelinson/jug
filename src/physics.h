#ifndef PHYSICS_H
#define PHYSICS_H

#include <QList>
#include <opencv/cv.h>
#include "climberstate.h"
#include "climberspecs.h"
#include "climbercoordinates.h"
#include "route.h"
#include "grip.h"
#include "globals.h"

class Physics
{
    friend class Climber;

public:
    Physics();
    bool isPossible(const ClimberState& pos) const;
    QList<ClimberState> configurations(const ClimberState& pos) const;
    bool isRouteLoaded() const;
    void fillInCom(ClimberState &pos, cv::Point com=cv::Point(-1, -1)) const;
    bool isReachableStart(const ClimberState& pos) const;
    cv::Point geometricCenter(const ClimberState& pos) const;
    bool analyzeForces(const ClimberState& pos) const;
    cv::Point supportForce(const Grip* g, Limb l, cv::Point slope) const;

private:
    void loadClimber(const ClimberSpecs &specs);
    void loadRoute(const Route* r);

    bool checkDistances(const ClimberCoordinates& coord, const cv::Point& com) const;
    bool checkLimbCrossing(const ClimberCoordinates& coord) const;
    bool checkFeetAboveHands(const ClimberCoordinates& coord) const;
    bool checkForHandHolds(const ClimberCoordinates& coord) const;
    bool checkLimbsPerGrip(const ClimberState &pos, const ClimberCoordinates &coord) const;

    bool compareForces(const cv::Point& gravity, const cv::Point& support) const;

    const Route* _route;
    ClimberSpecs _specs;
};

#endif // PHYSICS_H
