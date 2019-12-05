#include "edge.hpp"

#include <limits>

#include <QInputDialog>
#include <QDebug>

Edge::Edge(Node* s, Node* e, int w)
    : start(s)
    , end(e)
    , nodeWeight(w)
{
    setFlag(ItemIsSelectable);
}

QRectF Edge::boundingRect() const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentCoords();

    QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(currentCoords.first, currentCoords.second));

    return item->boundingRect();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen("orange");
    pen.setWidth(3);
    painter->setPen(pen);

    start->setZValue(1);
    end->setZValue(1);

    std::pair<QPointF, QPointF> currentCoords = getCurrentCoords();

    painter->drawLine(currentCoords.first, currentCoords.second);

    drawNodeWeight(painter);
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        this->setVisible(false);
        start->removeNeighbour(end);
        end->removeNeighbour(start);
    }
}

void Edge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    QString label = "Change weight for {" + QString::number(start->getNodeNumber())
                    + ", " + QString::number(end->getNodeNumber()) + "} edge:";

    bool ok;
    QString enteredValue = QInputDialog::getText(nullptr, "Edit", label, QLineEdit::Normal,
                                                 "0", &ok);

    if (ok && !enteredValue.isEmpty())
    {
        nodeWeight = enteredValue.compare("Inf") == 0 ?
                     enteredValue.toInt() :
                     std::numeric_limits<int>::max();
    }
}

std::pair<QPointF, QPointF> Edge::getCurrentCoords() const
{
    qreal startX = start->getX() + start->scenePos().x() + Node::radius/2;
    qreal startY = start->getY() + start->scenePos().y() + Node::radius/2;

    qreal endX = end->getX() + end->scenePos().x() + Node::radius/2;
    qreal endY = end->getY() + end->scenePos().y() + Node::radius/2;

    return std::make_pair(QPointF(startX, startY),
                          QPointF(endX, endY));
}

void Edge::drawNodeWeight(QPainter* painter) const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentCoords();
    qreal lineAngle = QLineF(currentCoords.first, currentCoords.second).angle();

    painter->save();
    painter->translate((currentCoords.first + currentCoords.second)/2);
    painter->rotate(-lineAngle);

    QString value = nodeWeight == std::numeric_limits<int>::max() ? "Inf" : QString::number(nodeWeight);
    painter->drawText(0, -10, value);
    painter->restore();
}




