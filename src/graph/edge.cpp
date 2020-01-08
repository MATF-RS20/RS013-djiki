#include "edge.hpp"

#include <limits>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QDebug>

Edge::Edge(Node* s, Node* e, int w, bool curve, QWidget* p)
    : start(s)
    , end(e)
    , edgeWeight(w)
    , curve(curve)
    , parent(p)
{
    animate = false;
    currentStep = 0;

    setFlag(ItemIsSelectable);
}

QRectF Edge::boundingRect() const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();

    QRectF rect(currentCoords.first, currentCoords.second);
    rect = rect.normalized();
    rect.setTopLeft(rect.topLeft() + QPointF(-40, -40));
    rect.setBottomRight(rect.bottomRight() + QPointF(40, 40));

    return rect;
}

QPainterPath Edge::shape() const
{
    std::pair<QPointF, QPointF> currentCoords = getCurrentNodeCoords();
    QLineF line(currentCoords.first, currentCoords.second);
    line.translate(QPointF(-10, -10));
    QPointF topLeft = line.p1();
    QPointF topRight = line.p2();

    line.translate(QPointF(20, 20));
    QPointF bottomLeft = line.p1();
    QPointF bottomRight = line.p2();

    QPolygonF poly;
    poly << currentCoords.second
         << currentCoords.first
         << topLeft
         << topRight
         << bottomRight
         << bottomLeft
         << currentCoords.first;

    QPainterPath path;
    path.addPolygon(poly);

    return path;
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

        if (curve)
        {
            QPainterPath path;
            path.moveTo(currentCoords.first);

            QPointF control;
            if (start == end)
                control = QPointF((currentCoords.first + currentCoords.second)/2 + QPointF(-20, 30));
            else
                control = QPointF((currentCoords.first + currentCoords.second)/2 + QPointF(15, 15));

            path.quadTo(control, currentCoords.second);
            painter->strokePath(path, pen);
        }
        else
        {
            painter->drawLine(currentCoords.first, currentCoords.second);
        }
    }
    else
    {
        pen.setColor(Qt::red);
        painter->setPen(pen);

        QPointF second = (1.0 - currentStep)*currentCoords.first + currentStep*currentCoords.second;

        if (curve)
        {
            QPainterPath path;
            path.moveTo(currentCoords.first);
            QPointF control((currentCoords.first + currentCoords.second)/2 - QPointF(15, 15));
            path.quadTo(control, second);
            painter->strokePath(path, pen);
        }
        else
        {
            painter->drawLine(currentCoords.first, second);
        }
    }

    drawEdgeWeight(painter);

    if (start != end)
        drawArrow(painter);
}

std::pair<QPointF, QPointF> Edge::getCurrentNodeCoords() const
{
    qreal startX = start->getX() + start->scenePos().x() + Node::radius/2;
    qreal startY = start->getY() + start->scenePos().y() + Node::radius/2;

    qreal endX = end->getX() + end->scenePos().x() + Node::radius/2;
    qreal endY = end->getY() + end->scenePos().y() + Node::radius/2;

    if (start == end)
        return std::make_pair(QPointF(startX, startY) - QPointF(8, 0), QPointF(endX, endY) + QPointF(5, 20));
    else
        return std::make_pair(QPointF(startX, startY), QPointF(endX, endY));
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

    if (curve)
    {
        painter->rotate(180);
        painter->drawText(0, -20, value);
    }
    else
    {
        painter->drawText(0, -10, value);
    }

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

    if (curve)
    {
        if (line.angle() > 120 && line.angle() < 330)
            painter->rotate(-20);
        else
            painter->rotate(20);
    }

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

    currentStep += 0.1;

    if (currentStep > 1)
    {
        currentStep = 0;
        animate = false;
    }

    update();
}

void Edge::nodeMoved()
{
    /* When start or end is moved draw line again */
    update();
}




