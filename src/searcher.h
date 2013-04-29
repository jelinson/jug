#ifndef SEARCHER_H
#define SEARCHER_H

#include <QQueue>
#include <QMap>
#include "abstractproblemstate.h"
#include "abstractsearchproblem.h"

class Searcher
{
public:
    Searcher(AbstractSearchProblem* problem);
    QList<AbstractProblemState> bfs();

private:
    QList<AbstractProblemState> constructPath(AbstractProblemState last);

    AbstractSearchProblem* _problem;
    QQueue<AbstractProblemState> _frontier;
    QMap<AbstractProblemState, AbstractProblemState> _moves;
};

#endif // SEARCHER_H
