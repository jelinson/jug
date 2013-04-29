#include "climberstate.h"

using namespace cv;

ClimberState::ClimberState()
    : _com(-1, -1)
{
    for (int i = 0; i < N_LIMBS; ++i)
        _limbGrips[i] = -1;
}

ClimberState::ClimberState(int lh, int rh, int lf, int rf, Point com)
    : _com(com)
{
    _limbGrips[LeftHand] = lh;
    _limbGrips[RightHand] = rh;
    _limbGrips[LeftFoot] = lf;
    _limbGrips[RightFoot] = rf;
}

void ClimberState::move(ClimberState::Limb l, int grip, Point com)
{
    _limbGrips[l] = grip;
    _com = com;
}
