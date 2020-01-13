#include "collectionalgorithm.hpp"

CollectionAlgorithm::CollectionAlgorithm()
{}

CollectionAlgorithm::CollectionAlgorithm(Collection *c)
    : collection(*c)
{
}

void CollectionAlgorithm::setCollection(Collection c)
{
    collection = c;
}


QVector<CollectionState> CollectionAlgorithm::getStates() const
{
    return states;
}

void CollectionAlgorithm::addState(Item* currentItem, unsigned currentLine, QVector<int> currentCollcetionSnapshot = QVector<int>())
{
    this->states.append(CollectionState(currentItem, nullptr, currentCollcetionSnapshot, currentLine));
}

void CollectionAlgorithm::addState(Item* currentItem, Item* currentItemSecond, unsigned currentLine, QVector<int> currentCollcetionSnapshot = QVector<int>())
{
    this->states.append(CollectionState(currentItem, currentItemSecond, currentCollcetionSnapshot, currentLine));
}

