#include "climberspecs.h"

ClimberSpecs::ClimberSpecs()
    : weight(CS_WEIGHT),
      armMin(CS_LIMB_MIN),
      armMax(CS_LIMB_MAX),
      legMin(CS_LIMB_MIN),
      legMax(CS_LIMB_MAX)
{
    sanityCheck();
}

ClimberSpecs::ClimberSpecs(int w, int amin, int amax, int lmin, int lmax)
    : weight(w), armMin(amin), armMax(amax), legMin(lmin), legMax(lmax)
{
    sanityCheck();
}

void ClimberSpecs::sanityCheck() const
{
    Q_ASSERT(weight >= 0);
    Q_ASSERT(armMin >= 0);
    Q_ASSERT(armMax >= 0);
    Q_ASSERT(legMin >= 0);
    Q_ASSERT(legMax >= 0);
}

bool ClimberSpecs::ok(Limb l, int dist)
{
    Q_ASSERT(dist >= 0);
    if (IS_ARM(l))
        return (armMin <= dist) && (dist <= armMax);
    else if (IS_LEG(l))
        return (legMin <= dist) && (dist <= legMax);
    else {
        qWarning() << "Invalid limb";
        return false;
    }
}

QDebug operator<<(QDebug d, const ClimberSpecs& specs)
{
    d.nospace() << "Specs:: weight: "
                << specs.weight
                << ", arm min: "
                << specs.armMin
                << ", arm max: "
                << specs.armMax
                << ", leg min: "
                << specs.legMin
                << ", leg max "
                << specs.legMax;
    return d.nospace();
}
