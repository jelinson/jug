#ifndef CLIMBER_H
#define CLIMBER_H

#include "climberspecs.h"
#include "pathproblem.h"
#include "physics.h"
#include "route.h"
#include "searcher.h"
#include "globals.h"

class Climber
{
public:
    Climber(const ClimberSpecs& specs, Physics *engine);
    void setSpecs(const ClimberSpecs& specs);
    void setEngine(Physics *engine);
    void climb(Route& r, bool visualize=true);

private:
    ClimberState start(Route& r);
    void visualize(Route& r, Path& p);

    Physics *_engine;
    ClimberSpecs _specs;
};

#endif // CLIMBER_H
