#ifndef CLIMBERSTATE_H
#define CLIMBERSTATE_H

#include <opencv/cv.h>

#define N_LIMBS 4

class ClimberState
{
public:
    ClimberState();
    ClimberState(int lh, int rh, int lf, int rf, cv::Point com);
    enum Limb {
        LeftHand = 0,
        RightHand = 1,
        LeftFoot = 2,
        RightFoot = 3
    };
    void move(Limb l, int grip, cv::Point com);

private:
    cv::Point _com;
    int _limbGrips[N_LIMBS];
};

#endif // CLIMBERSTATE_H
