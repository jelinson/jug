#ifndef ABSTRACTSEARCHPROBLEM_H
#define ABSTRACTSEARCHPROBLEM_H

#include  <QList>
#include "abstractproblemstate.h"

class AbstractSearchProblem
{
public:
    virtual AbstractProblemState start() = 0;
    virtual QList<AbstractProblemState> expand(AbstractProblemState currentState) = 0;
    virtual bool isGoal(AbstractProblemState currentState) = 0;
};

#endif // ABSTRACTSEARCHPROBLEM_H
