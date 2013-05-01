#include "physics.h"

using namespace cv;

Physics::Physics()
{
}

bool Physics::isPossible(const ClimberState &pos) const
{
    return false;
}

QList<ClimberState> Physics::configurations(const ClimberState &pos) const
{
    return QList<ClimberState>();
}

void Physics::loadClimber(const ClimberSpecs &specs)
{
}


void Physics::fillInCom(ClimberState &state, Point com) const
{
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


void Physics::loadRoute(const Route *r)
{
    _route = r;
}
