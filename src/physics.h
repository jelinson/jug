#ifndef PHYSICS_H
#define PHYSICS_H

#include <QList>
#include "climberstate.h"

class Physics
{
public:
    Physics();
    bool isPossible(const ClimberState& pos) const;
    QList<ClimberState> configurations(const ClimberState& pos) const;

private:
    bool placeholder;
};

#endif // PHYSICS_H
