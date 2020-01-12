#include "item.hpp"

#include <QPainter>
#include <QPen>
#include <QDebug>

unsigned Item::itemWidth = 40;
unsigned Item::itemHeight = 35;

Item::Item(double x, double y)
    : itemPosX(x)
    , itemPosY(y)
{
    setFlag(ItemIsMovable);
}

QRectF Item::boundingRect() const
{
    return QRectF(itemPosX, itemPosY, itemWidth, itemHeight);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen("#0e5a77");
    pen.setWidth(3);
    painter->setPen(pen);

    painter->drawRect(boundingRect());
}
