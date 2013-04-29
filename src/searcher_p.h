#include <QList>
#include <QQueue>
#include <QMap>
#include <QDebug>

template <typename State>
typename QList<State>::State Searcher<State>::bfs(AbstractProblem<State>* problem)
{
    State start = problem->start();
    QQueue<State> frontier;
    QMap<State, State> moves;
    frontier.enqueue(start);

    while (!frontier.isEmpty()) {
        State current = frontier.dequeue();

        if (problem->isGoal(current))
            return constructPath(current, start, moves);

        QList<State> neighbors = problem->expand(current);
        foreach (State next, neighbors) {
            if (!frontier.contains(next) && !moves.contains(next)) {
                moves.insert(next, current);
                frontier.enqueue(next);
            }
        }
    }

    qDebug() << "No path found";
    return QList<State>();
}
