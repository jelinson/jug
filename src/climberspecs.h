#ifndef CLIMBERSPECS_H
#define CLIMBERSPECS_H

#include "climberstate.h"
#include "globals.h"

struct ClimberSpecs {
    ClimberSpecs();
    ClimberSpecs(int w, int amin, int amax, int lmin, int lmax);
    void sanityCheck() const;
    bool ok(ClimberState::Limb l, int dist);
    int weight;
    int armMin, armMax;
    int legMin, legMax;
};

#endif // CLIMBERSPECS_H
