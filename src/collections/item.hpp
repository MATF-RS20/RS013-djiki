#ifndef ITEM_HPP
#define ITEM_HPP}

#include <QGraphicsItem>

class Item : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Item(double x, double y);

private:
    double itemPosX;
    double itemPosY;
};

#endif // ITEM_HPP
