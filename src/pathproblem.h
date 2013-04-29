#ifndef PATHPROBLEM_H
#define PATHPROBLEM_H

#include <QList>
#include "abstractproblem.h"
#include "climberstate.h"
#include "route.h"

template<typename T>
class PathProblem : public AbstractProblem<T>
{

};

template <>
class PathProblem<ClimberState> : public AbstractProblem<ClimberState>
{
public:
    PathProblem(Route toSolve) : _route(toSolve) {}
    virtual ClimberState start() const { return ClimberState(); }
    virtual QList<ClimberState> expand(const ClimberState &current) const
    { return QList<ClimberState>(); }
    virtual bool isGoal(const ClimberState &current) const { return false; }
private:
    Route _route;
};

#include "pathproblem_p.h"

#endif // PATHPROBLEM_H
