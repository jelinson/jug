#include "climbercoordinates.h"

ClimberCoordinates::ClimberCoordinates(const ClimberState &state, const Route *route)
{
    for (int i = 0; i < N_LIMBS; ++i) {
        int gripIndex = state.getGrip((ClimberState::Limb) i);
        _pos[i] = (*route)[gripIndex]->getCom();
    }
}

cv::Point ClimberCoordinates::operator [](int i) const
{
    return _pos[i];
}
