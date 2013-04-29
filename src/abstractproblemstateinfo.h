#ifndef ABSTRACTPROBLEMSTATEINFO_H
#define ABSTRACTPROBLEMSTATEINFO_H

class AbstractProblemStateInfo
{
public:
    inline int getCanonicalRep() const
    { return _canonical; }

protected:
    friend class AbstractProblemState;
    int _canonical;
};

bool operator<(const AbstractProblemStateInfo& a, const AbstractProblemStateInfo& b)
{
    return a.getCanonicalRep() < b.getCanonicalRep();
}

#endif // ABSTRACTPROBLEMSTATEINFO_H
