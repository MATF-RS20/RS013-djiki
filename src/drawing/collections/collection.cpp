#include "collection.hpp"

Collection::Collection()
{}

Collection::Collection(QVector<Item*> *items) : items(items)
{}

Item* Collection::getItemByItemNumber(unsigned n) const
{
    if(n > static_cast<unsigned>(items->size()))
        return nullptr;
    else
        return items->at(static_cast<int>(n));
}

const Item* Collection::getNextItem(Item* item) const
{
    unsigned index = item->getItemIndex();
    if(index + 1 >= static_cast<unsigned>(items->size()))
        return nullptr;
    else
        return items->at(static_cast<int>(index+1));
}

const Item* Collection::getPreviousItem(Item* item) const
{
    int index = static_cast<int>(item->getItemIndex());
    if(index - 1 < 0)
        return nullptr;
    else
        return items->at(index-1);
}

const QVector<Item*> Collection::getItems() const
{
    return *items;
}

unsigned Collection::getCollectionSize()
{
    return static_cast<unsigned>(this->items->size());
}
