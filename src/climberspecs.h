#ifndef CLIMBERSPECS_H
#define CLIMBERSPECS_H

#include "climberstate.h"

struct ClimberSpecs {
    ClimberSpecs(w, amin, amax, lmin, lmax);
    bool ok(ClimberState::Limb l, int dist);
    int weight;
    int armMin, armMax;
    int legMin, legMax;
};

#endif // CLIMBERSPECS_H
