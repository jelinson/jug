#include "searcher.h"
#include <QQueue>
#include <QDebug>

Searcher::Searcher()
{
}

Path Searcher::bfs(PathProblem &p)
{
    ClimberState start = p.start();
    QQueue<ClimberState> frontier;
    frontier.enqueue(start);
    QMap<ClimberState, ClimberState> moves;

    while (!frontier.isEmpty()) {
        ClimberState current = frontier.dequeue();

        if (p.isGoal(current))
            return recoverPath(current, start, moves);

        QList<ClimberState> neighbors = p.expand(current);
        foreach (ClimberState next, neighbors) {
            if (!moves.contains(next) && !frontier.contains(next)) {
                frontier.enqueue(next);
                moves.insert(next, current);
            }
        }
    }
    qWarning() << "No solution path found";
    return Path();
}

Path Searcher::recoverPath(const ClimberState &end,
                           const ClimberState &start,
                           const QMap<ClimberState, ClimberState> &moves)
{
    Path p;
    ClimberState current = end;
    while (current != start) {
        p.prepend(current);

        Q_ASSERT(moves.contains(current));
        current = moves[current];
    }
    return p;
}
