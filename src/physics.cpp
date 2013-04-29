#include "physics.h"

Physics::Physics()
{
}

bool Physics::isPossible(const ClimberState &pos) const
{
    return false;
}

QList<ClimberState> Physics::configurations(const ClimberState &pos) const
{
    return QList<ClimberState>();
}
