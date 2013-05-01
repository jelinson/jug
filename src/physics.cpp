#include "physics.h"

using namespace cv;

Physics::Physics()
    : _route(NULL)
{
}

bool Physics::isPossible(const ClimberState &pos) const
{
    Q_ASSERT(isRouteLoaded());
    return false;
}

QList<ClimberState> Physics::configurations(const ClimberState &pos) const
{
    Q_ASSERT(isRouteLoaded());
    return QList<ClimberState>();
}

void Physics::loadClimber(const ClimberSpecs &specs)
{
    _specs = specs;
}


void Physics::fillInCom(ClimberState &state, Point com) const
{
    Q_ASSERT(isRouteLoaded());
    if (com.x != -1 && com.y != -1)
        state._com = com;
    else {
        Point avg;
        int smudges = 0;
        for (int i = 0; i < N_LIMBS; ++i) {
            int gripIndex = state.getGrip((ClimberState::Limb) i);
            if (gripIndex != -1)
                avg += (*_route)[gripIndex]->getCom();
            else
                ++smudges;
        }
        avg.x /= (N_LIMBS - smudges);
        avg.y /= (N_LIMBS - smudges);
        state._com = avg;
    }
}

bool Physics::isReachableStart(const ClimberState &pos)
{
    Q_ASSERT(isRouteLoaded());

    int llegIndex = pos.getGrip(ClimberState::LeftFoot);
    int rlegIndex = pos.getGrip(ClimberState::RightFoot);

    Q_ASSERT(llegIndex < _route->nGrips());
    Q_ASSERT(rlegIndex < _route->nGrips());

    bool possible = false;
    if (llegIndex != -1)
        possible = possible | ((*_route)[llegIndex]->getCom().y < CS_LIMB_MAX);

    if(rlegIndex != -1)
        possible = possible | ((*_route)[rlegIndex]->getCom().y < CS_LIMB_MAX);

    return possible;
}

void Physics::loadRoute(const Route *r)
{
    _route = r;
}

bool Physics::isRouteLoaded() const
{
    return _route != NULL;
}
