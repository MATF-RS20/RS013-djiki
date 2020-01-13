#ifndef COLLECTIONSTATE_H
#define COLLECTIONSTATE_H

#include "../../drawing/collections/item.hpp"


struct CollectionState {
    CollectionState() {}
    CollectionState(Item* currentItem, Item* currentItemSecond,
                    QVector<int>currentCollcetionSnapshot, unsigned currentLine)
        : currentItem(currentItem)
        , currentItemSecond(currentItemSecond)
        , currentCollcetionSnapshot(currentCollcetionSnapshot)
        , currentLine(currentLine)
    {}

    Item* currentItem;
    Item* currentItemSecond;
    QVector<int>currentCollcetionSnapshot;
    unsigned currentLine;
};



#endif // COLLECTIONSTATE_H
