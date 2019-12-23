#include "edge.hpp"

#include <limits>

#include <QInputDialog>
#include <QDebug>

Edge::Edge(Node* s, Node* e, int w, QWidget* p)
    : start(s)
    , end(e)
    , edgeWeight(w)
    , parent(p)
{
    animate = false;
    animationStep = 0;

    setFlag(ItemIsSelectable);
}

QRectF Edge::boundingRect() const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();

    QRectF rect(currentCoords.first, currentCoords.second);
    rect = rect.normalized();
    rect.setTopLeft(rect.topLeft() + QPointF(-30, -30));
    rect.setBottomRight(rect.bottomRight() + QPointF(35, 35));

    return rect;
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPen pen;
    pen.setWidth(3);

    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();

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
        QPointF second = (1.0 - animationStep)*currentCoords.first + animationStep*currentCoords.second;
        painter->drawLine(currentCoords.first, second);
    }

    drawEdgeWeight(painter);
    drawArrow(painter);
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

void Edge::drawEdgeWeight(QPainter* painter) const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();
    qreal lineAngle = QLineF(currentCoords.first, currentCoords.second).angle();

    painter->save();
    painter->translate((currentCoords.first + currentCoords.second)/2);
    painter->rotate(-lineAngle);

    if (lineAngle > 100 && lineAngle < 270)
        painter->rotate(180);

    QString value = edgeWeight == std::numeric_limits<int>::max() ? "Inf" : QString::number(edgeWeight);
    painter->drawText(0, -10, value);

    painter->restore();
}

void Edge::drawArrow(QPainter *painter) const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();
    QLineF line = QLineF(currentCoords.first, currentCoords.second);

    painter->save();

    QPolygonF endPolygon = end->mapToScene(end->shape().toFillPolygon());

    QPointF intersectPoint;
    QPointF p1 = endPolygon.first();

    for (int i = 1; i < endPolygon.count(); i++)
    {
        QPointF p2 = endPolygon.at(i);
        QLineF polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectionType = polyLine.intersect(line, &intersectPoint);

       if (intersectionType == QLineF::BoundedIntersection)
           break;

       p1 = p2;
    }

    painter->translate(intersectPoint);

    QRectF rect(0, 0, 20, 10);
    rect.moveCenter(QPointF(0, 0));

    painter->rotate(-line.angle());

    painter->drawLine(rect.topLeft(), QPointF(0, 0));
    painter->drawLine(rect.bottomLeft(), QPointF(0, 0));

    painter->restore();
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        scene()->removeItem(this);

        start->removeNeighbour(end);
        end->removeNeighbour(start);
    }
}

void Edge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)
{
    QString label = "Change weight for {" + QString::number(start->getNodeNumber())
                    + ", " + QString::number(end->getNodeNumber()) + "} edge:";

    bool status;
    QString enteredValue = QInputDialog::getText(parent, "Edit", label, QLineEdit::Normal,
                                                 "0", &status);

    if (status && !enteredValue.isEmpty())
    {
        edgeWeight = enteredValue == "Inf" ?
                     std::numeric_limits<int>::max() :
                     enteredValue.toInt();
    }

    update();
}

Node* Edge::getStart() const
{
    return start;
}

Node* Edge::getEnd() const
{
    return end;
}

int Edge::getEdgeWeight() const
{
    return edgeWeight;
}

void Edge::animateEdge()
{
    animate = true;
}

void Edge::advance(int phase)
{
    if (!phase || !animate)
        return;

    animationStep += 0.1;

    if (animationStep > 1)
    {
        animationStep = 0;
        animate = false;
    }

    update();
}

void Edge::nodeMoved()
{
    /* When start or end is moved draw line again */
    update();
}




