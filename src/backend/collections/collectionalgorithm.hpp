#ifndef COLLECTIONALGORITHM_HPP
#define COLLECTIONALGORITHM_HPP
#include "collectionstate.hpp"
#include "../../drawing/collections/collection.hpp"
#include "../pseudocode.hpp"
#include "../algorithm.hpp"

class CollectionAlgorithm : public Algorithm
{
public:
    CollectionAlgorithm();
    CollectionAlgorithm(Collection *c);

    void setCollection(Collection c);
    virtual void solve() = 0;
    virtual ~CollectionAlgorithm() = default;

    QVector<CollectionState> getStates() const;

protected:
    void addState(Item* currentItem, unsigned currentLine, QVector<int> currentCollcetionSnapshot = QVector<int>());
    void addState(Item* currentItem, Item* currentItemSecond, unsigned currentLine, QVector<int> currentCollcetionSnapshot = QVector<int>());

    Collection collection;
    QVector<CollectionState> states;
};

#endif // GRAPHALGORITHM_HPP
