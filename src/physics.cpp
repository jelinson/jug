#include "physics.h"

using namespace cv;

Physics::Physics()
    : _route(NULL)
{
    // nothing to do
}

bool Physics::isPossible(const ClimberState &pos) const
{
    /// \refactor like whoa

    Q_ASSERT(isRouteLoaded());
    Point avg = geometricCenter(pos);

    ClimberCoordinates coord(pos, _route);

    // check distances
    for (int i = 0; i < N_LIMBS; ++i) {
        Point diff = coord[i] - avg;
        int dist = abs(norm(diff));

        if (dist > CS_LIMB_MAX || dist < CS_LIMB_MIN)
            return false;
    }

    // check limb crossing
    if (coord[(int) ClimberState::LeftHand].x > coord[(int) ClimberState::RightHand].x)
        return false;

    if (coord[(int) ClimberState::LeftFoot].x > coord[(int) ClimberState::RightFoot].x)
        return false;

    // check feet below hands
    int highestArm = min(coord[(int) ClimberState::LeftHand].y,
                         coord[(int) ClimberState::RightHand].y);

    int lowestLeg = max(coord[(int) ClimberState::LeftFoot].y,
                        coord[(int) ClimberState::RightFoot].y);

    // if feet above hands
    if (lowestLeg < highestArm)
        return false;

    // sanity check holds
    int leftArmIndex = pos.getGrip(ClimberState::LeftHand);
    int rightArmIndex = pos.getGrip(ClimberState::RightHand);

    if (!(*_route)[leftArmIndex]->handHold() || !(*_route)[rightArmIndex]->handHold())
        return false;

    /// \todo nLimbs check

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

    ClimberCoordinates coord(pos, _route);

    // half the weight is in the center of mass, the other half is distributed
    // among the four limbs
    Point gravity(0, _specs.weight / 2);
    Point support(0, 0);

    for (int i = 0; i < N_LIMBS; ++i) {
        Point slope = Geometry::discreteSlope(coord[i], pos._com);

        Point limbForce;
        if (slope.y < 0)
            limbForce = Point(slope.x, -slope.y);
        else
            limbForce = slope;
        gravity += limbForce * (_specs.weight / (2 * N_LIMBS));

        int gripIndex = pos.getGrip((ClimberState::Limb) i);
        Point gripForce = supportForce((*_route)[gripIndex], (ClimberState::Limb) i, slope);
        support += gripForce;
    }

    return (-support.y >= gravity.y && abs(support.x + gravity.x) < LATERAL_SELF_BALANCE);
}

Point Physics::supportForce(const Grip *g, ClimberState::Limb l, Point slope) const
{
    // feet push up
    if (l == ClimberState::LeftFoot || ClimberState::RightFoot)
        slope = -1 * slope;

    return slope * min(g->_nf.lookUp(slope), 1) * g->_area * AREA_FORCE_SCALING;
}

void Physics::loadRoute(const Route *r)
{
    _route = r;
}

bool Physics::isRouteLoaded() const
{
    return _route != NULL;
}
