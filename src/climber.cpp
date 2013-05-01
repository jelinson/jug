#include "climber.h"

Climber::Climber(const ClimberSpecs &specs, Physics *engine)
    : _specs(specs), _engine(engine)
{
    _engine->loadClimber(_specs);
}


void Climber::climb(Route &r, bool visualize)
{
    _engine->loadRoute(&r);

}

ClimberState Climber::start(Route &r)
{
    ClimberState();
}

void Climber::visualize(Route &r, Path &p)
{
    // placeholder
}
