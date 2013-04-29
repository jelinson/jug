#ifndef SEARCHER_H
#define SEARCHER_H

#include <QList>
#include <QQueue>
#include <QMap>
#include "abstractproblem.h"

template<typename State>
class Searcher
{
public:
    static typename QList<State>::State bfs(AbstractProblem<State>* problem);

private:
    static QList<State> constructPath(const State& last,
                                      const State& start,
                                      const QMap<State, State>& );
};

#include "searcher_p.h"

#endif // SEARCHER_H
