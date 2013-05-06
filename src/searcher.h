#ifndef SEARCHER_H
#define SEARCHER_H

#include <QList>
#include <QMap>
#include "climberstate.h"
#include "pathproblem.h"
#include "globals.h"


class Searcher
{
public:
    Searcher();
    static Path bfs(PathProblem& p);
    static Path aStart(PathProblem& p);

private:
    static Path recoverPath(const ClimberState& end,
                            const ClimberState& start,
                            const QMap<ClimberState, ClimberState>& moves);
};

#endif // SEARCHER_H
