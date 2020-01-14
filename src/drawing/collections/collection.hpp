#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "item.hpp"
#include <QVector>

class Collection
{
public:
    Collection();
    Collection(QVector<Item*> *items);

    Item* getItemByItemNumber(unsigned n) const;

    const Item* getNextItem(Item* item) const;
    const Item* getPreviousItem(Item* item) const;
    const QVector<Item*> getItems() const;

    unsigned getCollectionSize();
private:
    QVector<Item*> *items;
};

#endif // COLLECTION_HPP

