#include "connection.hpp"

#include <QPainter>
#include <QPen>
#include <QGraphicsScene>

Connection::Connection(Item* first, Item* second)
    : first(first)
    , second(second)
{
    animate = false;
    currentStep = 0;
}

QRectF Connection::boundingRect() const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentItemCoords();

    QRectF rect(currentCoords.first, currentCoords.second);
    rect = rect.normalized();
    rect.setTopLeft(rect.topLeft() + QPointF(-30, -30));
    rect.setBottomRight(rect.bottomRight() + QPointF(30, 30));

    return rect;
}

void Connection::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPen pen;
    pen.setWidth(3);

    std::pair<QPointF, QPointF> currentCoords = getCurrentItemCoords();

    if (!animate)
    {
        pen.setColor("orange");
        painter->setPen(pen);

        painter->drawLine(currentCoords.first, currentCoords.second);
    }
    else
    {
        pen.setColor(Qt::red);
        painter->setPen(pen);

        QPointF second = (1.0 - currentStep)*currentCoords.first + currentStep*currentCoords.second;

        painter->drawLine(currentCoords.first, second);
    }
}

void Connection::advance(int phase)
{
    if (!phase || !animate)
        return;

    currentStep += 0.1;

    if (currentStep > 1)
    {
        currentStep = 0;
        animate = false;
    }

    update();
}

void Connection::animateConnection()
{
    animate = true;
}

void Connection::itemMoved()
{
    update();
}

std::pair<QPointF, QPointF> Connection::getCurrentItemCoords() const
{
    /* Get collection item coordinates after moving -> scene position changes.
       This is needed to make edge "follow" item when it is moving */

    qreal firstX = first->getItemPosX() + first->scenePos().x() + Item::itemWidth/2;
    qreal firstY = first->getItemPosY() + first->scenePos().y() + Item::itemHeight/2;

    qreal secondX = second->getItemPosX() + second->scenePos().x() + Item::itemWidth/2;
    qreal secondY = second->getItemPosY() + second->scenePos().y() + Item::itemHeight/2;

    return std::make_pair(QPointF(firstX, firstY), QPointF(secondX, secondY));
}
