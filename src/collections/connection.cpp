#include "connection.hpp"

#include <QPainter>
#include <QPen>

Connection::Connection(Item *first, Item *second)
    : first(first)
    , second(second)
{}

QRectF Connection::boundingRect() const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentItemCoords();

    QRectF rect(currentCoords.first, currentCoords.second);
    rect = rect.normalized();
    rect.setTopLeft(rect.topLeft() + QPointF(-40, -40));
    rect.setBottomRight(rect.bottomRight() + QPointF(40, 40));

    return rect;
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPen pen;
    pen.setColor("orange");
    pen.setWidth(3);
    painter->setPen(pen);

    std::pair<QPointF, QPointF> currentCoords = getCurrentItemCoords();

    painter->drawLine(currentCoords.first, currentCoords.second);
}

void Connection::itemMoved()
{
    update();
}

std::pair<QPointF, QPointF> Connection::getCurrentItemCoords() const
{
    qreal firstX = first->getItemPosX() + first->scenePos().x() + Item::itemWidth/2;
    qreal firstY = first->getItemPosY() + first->scenePos().y() + Item::itemHeight/2;

    qreal secondX = second->getItemPosX() + second->scenePos().x() + Item::itemWidth/2;
    qreal secondY = second->getItemPosY() + second->scenePos().y() + Item::itemHeight/2;

    return std::make_pair(QPointF(firstX, firstY), QPointF(secondX, secondY));
}
