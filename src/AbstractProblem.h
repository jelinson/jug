#ifndef ABSTRACTPROBLEM_H
#define ABSTRACTPROBLEM_H

#include <QList>

template<typename T>
class AbstractProblem {
public:
    virtual T start() const = 0;
    virtual QList<T> expand(const T& current) const = 0;
    virtual bool isGoal(const T& current) const = 0;
};

#endif // ABSTRACTPROBLEM_H
