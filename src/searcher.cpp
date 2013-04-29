#include "searcher.h"

Searcher::Searcher(AbstractSearchProblem *problem)
    : _problem(problem)
{
    // Nothing to do
}

QList<AbstractProblemState> Searcher::bfs()
{
    _frontier.clear();
    _moves.clear();

    AbstractProblemState start = _problem->start();
    _frontier.enqueue(start);

    while (!_frontier.isEmpty()) {
        AbstractProblemState current = _frontier.dequeue();

        if (_problem->isGoal(current))
            return constructPath(current);

        QList<AbstractProblemState> expansion = _problem->expand(current);
        foreach (AbstractProblemState next, expansion) {
            if (!_moves.contains(next) && !_frontier.contains(next)) {
                _frontier.enqueue(next);
                _moves.insert(next, current);
            }
        }
    }
}

QList<AbstractProblemState> Searcher::constructPath(AbstractProblemState last)
{
    QList<AbstractProblemState> path;
    AbstractProblemState current = last;
    while (!current.isStart()) {
        Q_ASSERT(_moves.contains(current));
        path.prepend(current);
        current = _moves[current];
    }
    return path;
}

