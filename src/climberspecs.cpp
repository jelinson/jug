#include "climberspecs.h"

ClimberSpecs::ClimberSpecs()
    : weight(CS_WEIGHT),
      armMin(CS_LIMB_MIN),
      armMax(CS_LIMB_MAX),
      legMin(CS_LIMB_MIN),
      legMax(CS_LIMB_MAX)
{
    // nothing to do
}

ClimberSpecs::ClimberSpecs(int w, int amin, int amax, int lmin, int lmax)
    : weight(w), armMin(amin), armMax(amax), legMin(lmin), legMax(lmax)
{
    // nothing to do
}

bool ClimberSpecs::ok(ClimberState::Limb l, int dist)
{
    if (IS_ARM(l))
        return (armMin <= dist) && (dist <= armMax);
    else if (IS_LEG(l))
        return (legMin <= dist) && (dist <= legMax);
    else {
        qWarning() << "Invalid limb";
        return false;
    }
}
