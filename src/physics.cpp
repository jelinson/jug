#include "physics.h"

using namespace cv;

Physics::Physics()
    : _route(NULL)
{
    // nothing to do
}

bool Physics::isPossible(const ClimberState &pos) const
{
    Q_ASSERT(isRouteLoaded());
    Point avg = geometricCenter(pos);

    // check distances
    for (int i = 0; i < N_LIMBS; ++i) {
        int gripIndex = pos.getGrip((ClimberState::Limb) i);
        Point diff = (*_route)[gripIndex]->getCom() - avg;
        int dist = abs(norm(diff));

        if (dist > CS_LIMB_MAX || dist < CS_LIMB_MIN)
            return false;
    }

    // check limb crossing



    return true;
}

QList<ClimberState> Physics::configurations(const ClimberState &pos) const
{
    Q_ASSERT(isRouteLoaded());

    QList<ClimberState> viableConfig;
    Point avg = geometricCenter(pos);

    for (int x = -LATTICE_DIM; x <= LATTICE_DIM; ++x) {
        for (int y = -LATTICE_DIM; y <= LATTICE_DIM; ++y) {
            Point adjCom = avg + Point(x * LATTICE_SPACING, y * LATTICE_SPACING);
            ClimberState adjPos = pos;
            adjPos.setCenter(adjCom);
            if (jug::validPoint(adjCom) && analyzeForces(adjPos))
                viableConfig.append(adjPos);
        }
    }

    return viableConfig;
}

void Physics::loadClimber(const ClimberSpecs &specs)
{
    _specs = specs;
}


void Physics::fillInCom(ClimberState &pos, Point com) const
{
    Q_ASSERT(isRouteLoaded());
    if (com.x != -1 && com.y != -1)
        pos._com = com;
    else
        pos._com = geometricCenter(pos);
}

bool Physics::isReachableStart(const ClimberState &pos) const
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

Point Physics::geometricCenter(const ClimberState &pos) const
{
    Q_ASSERT(isRouteLoaded());
    Point avg;
    int smudges = 0;
    for (int i = 0; i < N_LIMBS; ++i) {
        int gripIndex = pos.getGrip((ClimberState::Limb) i);
        if (gripIndex != -1)
            avg += (*_route)[gripIndex]->getCom();
        else
            ++smudges;
    }
    avg.x /= (N_LIMBS - smudges);
    avg.y /= (N_LIMBS - smudges);
    return avg;
}

bool Physics::analyzeForces(const ClimberState &pos) const
{
    Q_ASSERT(isRouteLoaded());


    return false;
}

void Physics::loadRoute(const Route *r)
{
    _route = r;
}

bool Physics::isRouteLoaded() const
{
    return _route != NULL;
}
