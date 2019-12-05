#include "edge.hpp"

Edge::Edge(Node* s, Node* e, int w)
    : start(s)
    , end(e)
    , nodeWeight(w)
{}

QRectF Edge::boundingRect() const
{
    return QRectF(QPointF(start->getX(), start->getY()),
                  QPointF(end->getX(), end->getY()));
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen("orange");
    pen.setWidth(3);

    start->setZValue(10);
    end->setZValue(10);

    painter->setPen(pen);
    painter->drawLine(QPointF(start->getX() + Node::radius/2, start->getY() + Node::radius/2),
                      QPointF(end->getX() + Node::radius/2, end->getY() + Node::radius/2));
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        delete this;
}

void Edge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    QString title = "Change weight for {" + QString::number(start->getNodeNumber())
                    + ", " + QString::number(end->getNodeNumber()) + "} edge.";

    bool ok;
    QString value = QInputDialog::getText(nullptr, title, "Weight: ", QLineEdit::Normal,
                                          "0", &ok);

    if (ok && !value.isEmpty())
    {
        nodeWeight = value.toInt();
    }
}




