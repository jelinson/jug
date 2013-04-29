#include "searcher.h"
#include <QQueue>
#include <QDebug>

Searcher::Searcher()
{
}

QList<ClimberState> Searcher::bfs(PathProblem &p)
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
    return QList<ClimberState>();
}

QList<ClimberState> Searcher::recoverPath(const ClimberState &end,
                                          const ClimberState &start,
                                          const QMap<ClimberState, ClimberState> &moves)
{
    QList<ClimberState> path;
    ClimberState current = end;
    while (current != start) {
        path.prepend(current);

        Q_ASSERT(moves.contains(current));
        current = moves[current];
    }
    return path;
}
