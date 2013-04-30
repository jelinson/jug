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
    Path bfs(PathProblem& p);

private:
    Path recoverPath(const ClimberState& end,
                                    const ClimberState& start,
                                    const QMap<ClimberState, ClimberState>& moves);
};

#endif // SEARCHER_H
