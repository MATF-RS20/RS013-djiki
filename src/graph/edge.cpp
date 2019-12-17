#include "edge.hpp"

#include <limits>

#include <QInputDialog>
#include <QDebug>

Edge::Edge(Node* s, Node* e, int w, QWidget* p)
    : start(s)
    , end(e)
    , nodeWeight(w)
    , parent(p)
{
    setFlag(ItemIsSelectable);
}

QRectF Edge::boundingRect() const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();

    QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(currentCoords.first, currentCoords.second));
    QRectF rect = item->boundingRect();

    return QRectF(rect.topLeft() + QPointF(-20, -20),
                  rect.bottomRight() + QPointF(30, 30)).normalized();
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    /* Draw edge with different color if edge is active in algorithm visualization */
    QPen pen(edgeColor);
    pen.setWidth(3);
    painter->setPen(pen);

    start->setZValue(5);
    end->setZValue(5);

    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();

    painter->drawLine(currentCoords.first, currentCoords.second);

    // Debug boundingRect
//    pen.setWidth(1);
//    pen.setColor(Qt::white);
//    painter->setPen(pen);
//    painter->drawRect(boundingRect());

    drawNodeWeight(painter);
}

std::pair<QPointF, QPointF> Edge::getCurrentNodeCoords() const
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
    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();
    qreal lineAngle = QLineF(currentCoords.first, currentCoords.second).angle();

    painter->save();
    painter->translate((currentCoords.first + currentCoords.second)/2);
    painter->rotate(-lineAngle);

    if (lineAngle > 100 && lineAngle < 270)
        painter->rotate(180);

    QString value = nodeWeight == std::numeric_limits<int>::max() ? "Inf" : QString::number(nodeWeight);
    painter->drawText(0, -10, value);
    painter->restore();
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

    bool status;
    QString enteredValue = QInputDialog::getText(parent, "Edit", label, QLineEdit::Normal,
                                                 "0", &status);

    if (status && !enteredValue.isEmpty())
    {
        nodeWeight = enteredValue == "Inf" ?
                     std::numeric_limits<int>::max() :
                     enteredValue.toInt();
    }

    update();
}

void Edge::setNodeColor(QColor& color)
{
    edgeColor = color;
    update();
}

Node *Edge::getStart() const
{
    return start;
}

Node *Edge::getEnd() const
{
    return end;
}

void Edge::nodeMoved()
{
    /* When start or end is moved draw line again */
    update();
}




