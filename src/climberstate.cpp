#include "climberstate.h"

using namespace cv;

QDebug operator<<(QDebug db, Limb l)
{
    switch ((int) l) {
    case (int) LeftArm:
        db << "leg arm";
        break;
    case (int) RightArm:
        db << "right arm";
        break;
    case (int) LeftLeg:
        db << "left leg";
        break;
    case (int) RightLeg:
        db << "right leg";
        break;
    }
    return db;
}

ClimberState::ClimberState()
    : _com(-1, -1)
{
    for (int i = 0; i < N_LIMBS; ++i)
        _limbGrips[i] = -1;
}

ClimberState::ClimberState(int lh, int rh, int lf, int rf, Point com)
    : _com(com)
{
    _limbGrips[LeftArm] = lh;
    _limbGrips[RightArm] = rh;
    _limbGrips[LeftLeg] = lf;
    _limbGrips[RightLeg] = rf;
}

ClimberState::ClimberState(const ClimberState &other)
    : _com(other._com)
{
    for (int i = 0; i < N_LIMBS; ++i)
        _limbGrips[i] = other._limbGrips[i];
}

int ClimberState::getGripIndex(Limb l) const
{
    return _limbGrips[l];
}

int ClimberState::getGripIndex(int i) const
{
    return getGripIndex((Limb) i);
}

ClimberState ClimberState::move(Limb l, int grip) const
{
    ClimberState next = *this;
    next._limbGrips[l] = grip;
    return next;
}

bool ClimberState::handOn(int grip) const
{
    return _limbGrips[LeftArm] == grip || _limbGrips[RightArm] == grip;
}

bool ClimberState::isEquivalent(const ClimberState &other) const
{
    bool flag = (_com == other._com);
    for (int i = 0; i < N_LIMBS; ++i)
        flag = flag & (_limbGrips[i] == other._limbGrips[i]);
    return flag;
}

bool ClimberState::compare(const ClimberState &a, const ClimberState &b)
{
    Q_ASSERT(a._com.y != -1);
    Q_ASSERT(b._com.y != -1);
    return a._com.y > b._com.y;
}

void ClimberState::setCenter(const Point &com)
{
    _com = com;
}

bool operator==(const ClimberState& a, const ClimberState& b)
{
    return a.isEquivalent(b);
}

bool operator!=(const ClimberState& a, const ClimberState& b)
{
    return !(a == b);
}

bool operator<(const ClimberState& a, const ClimberState& b)
{
    return ClimberState::compare(a, b);
}
