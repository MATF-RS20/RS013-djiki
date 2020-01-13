#include "algorithm.hpp"

Algorithm::Algorithm()
{

}

QString Algorithm::getOutcome() const
{
    return outcome;
}

QString Algorithm::getPseudoCodeHTML(unsigned activeLine) const
{
    return code.generateHTML(activeLine);
}
