#ifndef SEARCHER_H
#define SEARCHER_H

#include <QList>
#include <QMap>
#include "climberstate.h"
#include "pathproblem.h"


class Searcher
{
public:
    Searcher();
    QList<ClimberState> bfs(PathProblem& p);

private:
    QList<ClimberState> recoverPath(const ClimberState& end,
                                    const ClimberState& start,
                                    const QMap<ClimberState, ClimberState>& moves);
};

#endif // SEARCHER_H
