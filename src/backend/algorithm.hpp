#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#include <QString>
#include "pseudocode.hpp"

class Algorithm
{
public:
    Algorithm();

    virtual void solve() = 0;

    QString getOutcome() const;
    QString getPseudoCodeHTML(unsigned activeLine = 0) const;
    const Pseudocode& getCode() const;

protected:
    QString outcome;
    Pseudocode code;
};

#endif // ALGORITHM_HPP
