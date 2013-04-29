#ifndef ABSTRACTPROBLEMSTATE_H
#define ABSTRACTPROBLEMSTATE_H

#include "abstractproblemstateinfo.h"

class AbstractProblemState
{
public:
    AbstractProblemState() : _info(new AbstractProblemStateInfo) {}
    AbstractProblemState(const AbstractProblemState& other);
    ~AbstractProblemState()
    { delete _info; }

    inline const AbstractProblemStateInfo* getInfo() const
    { return _info; }

    inline const bool isStart() const
    { return _start; }

protected:
    bool _start;
    AbstractProblemStateInfo* _info;

};

bool operator==(const AbstractProblemState& a, const AbstractProblemState& b)
{
    return *(a.getInfo()) == *(b.getInfo());
}

bool operator<(const AbstractProblemState& a, const AbstractProblemState& b)
{
    return a.getInfo()->getCanonicalRep() == b.getInfo()->getCanonicalRep();
}

#endif // ABSTRACTPROBLEMSTATE_H
