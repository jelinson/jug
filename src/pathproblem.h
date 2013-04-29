#ifndef PATHPROBLEM_H
#define PATHPROBLEM_H

#include <QList>
#include "climberstate.h"
#include "physics.h"

class PathProblem
{
public:
    PathProblem(const ClimberState& start, int nGrips, int lastGrip);
    void setEngine(const Physics* engine);
    ClimberState start() const;
    QList<ClimberState> expand(const ClimberState& current);
    bool isGoal(const ClimberState& current);

private:
    const ClimberState _start;
    int _nGrips;
    int _goal;
    const Physics* _engine;
};

#endif // PATHPROBLEM_H
