#ifndef CLIMBERSTATE_H
#define CLIMBERSTATE_H

#include <opencv/cv.h>
#include "geometry.h"
#include "globals.h"

enum Limb {
    LeftArm = 0,
    RightArm = 1,
    LeftLeg = 2,
    RightLeg = 3
};
QDebug operator<<(QDebug db, Limb l);

class ClimberState
{
    friend class Physics;
    friend QDebug operator<<(QDebug db, const ClimberState& state);
public:
    ClimberState();
    ClimberState(int lh, int rh, int lf, int rf, cv::Point com=cv::Point(-1, -1));
    ClimberState(const ClimberState& other);

    int getGripIndex(Limb l) const;
    int getGripIndex(int i) const;
    int limbsOnGrip(int g) const;
    cv::Point getCom() const;
    ClimberState move(Limb l, int grip) const;
    bool handOn(int grip) const;
    bool isEquivalent(const ClimberState& other) const;

    static bool compare(const ClimberState& a, const ClimberState& b);

private:
    void setCenter(const cv::Point& com);
    cv::Point _com;
    int _limbGrips[N_LIMBS];
};

bool operator==(const ClimberState& a, const ClimberState& b);
bool operator!=(const ClimberState& a, const ClimberState& b);
bool operator<(const ClimberState& a, const ClimberState& b);
QDebug operator<<(QDebug db, const ClimberState& state);

#endif // CLIMBERSTATE_H
