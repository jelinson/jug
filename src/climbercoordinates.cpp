#include "climbercoordinates.h"

ClimberCoordinates::ClimberCoordinates(const ClimberState &state, const Route *route)
{
    for (int i = 0; i < N_LIMBS; ++i) {
        int gripIndex = state.getGripIndex(i);
        _grips.append((*route)[gripIndex]);
        _pos.append(_grips[i]->getCom());
    }
}

const Grip *ClimberCoordinates::getGrip(int i) const
{
    Q_ASSERT(i != -1);
    return _grips[i];
}

const Grip *ClimberCoordinates::getGrip(Limb i) const
{
    Q_ASSERT(i != -1);
    return _grips[(int) i];
}

cv::Point ClimberCoordinates::operator [](int i) const
{
    return _pos[i];
}

cv::Point ClimberCoordinates::operator [](Limb i) const
{
    return _pos[(int) i];
}
