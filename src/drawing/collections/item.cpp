#include "item.hpp"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

int Item::itemWidth = 40;
int Item::itemHeight = 35;
unsigned Item::index = 0;

Item::Item(qreal x, qreal y)
    : itemPosX(x)
    , itemPosY(y)
{
    itemIndex = index++;

    setZValue(10);
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

    QBrush brush("#0f1119");
    painter->setBrush(brush);

    QRectF rect = boundingRect();
    painter->drawRect(rect);

    painter->setFont(QFont("Times", 16, QFont::Bold));
    painter->drawText(rect, Qt::AlignCenter, QString::number(itemIndex));
}

void Item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit itemMoved();
    QGraphicsItem::mouseMoveEvent(event);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        if (this->itemIndex == index-1)
        {
            scene()->removeItem(this);
            emit itemDeleted(this);

            index--;
        }
    }
}

qreal Item::getItemPosX() const
{
    return itemPosX;
}

qreal Item::getItemPosY() const
{
    return itemPosY;
}
