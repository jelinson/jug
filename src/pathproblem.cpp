#include "pathproblem.h"

PathProblem::PathProblem(const ClimberState &start, int nGrips, int lastGrip)
    : _start(start), _nGrips(nGrips), _goal(lastGrip)
{
    // Nothing to do (yet!)
}

void PathProblem::setEngine(const Physics *engine)
{
    _engine = engine;
}

ClimberState PathProblem::start() const
{
    return _start;
}

Path PathProblem::expand(const ClimberState &current)
{
    QList<ClimberState> neighbors;
    for (int limb = 0; limb < N_LIMBS; ++limb) {
        for (int gripIndex = 0; gripIndex < _nGrips; ++gripIndex) {
        /// \todo revisit
        //for (int gripIndex = -1; gripIndex < _nGrips; ++gripIndex) {
            ClimberState next = current.move((Limb) limb, gripIndex);

            if (_engine->isPossible(next))
                foreach (ClimberState nextConfig, _engine->configurations(next))
                    neighbors.append(nextConfig);
        }
    }
    return neighbors;
}

bool PathProblem::isGoal(const ClimberState &current)
{
    Q_ASSERT(_goal != -1);
    return current.handOn(_goal);
}
