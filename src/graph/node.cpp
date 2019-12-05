#include "../graph/node.hpp"
#include <QApplication>

unsigned Node::numberOfNodes = 0;
unsigned Node::radius = 20;

Node::Node(double x, double y)
    : posX(x)
    , posY(y)
{ 
    pressed = false;

    nodeNumber = numberOfNodes++;
    setFlag(ItemIsMovable);
}

QRectF Node::boundingRect() const
{
    return QRectF(posX, posY, radius*1.5, radius*1.5);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen("#0e5a77");
    pen.setWidth(3);

    painter->setPen(pen);

    QBrush brush(Qt::white);
    painter->setBrush(brush);

    QRectF rect = boundingRect();
    painter->drawEllipse(rect);

    painter->setFont(QFont("Times", 16, QFont::Bold));
    painter->drawText(rect, Qt::AlignCenter, QString(std::to_string(nodeNumber).c_str()));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        delete this;
    else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        emit drawNeighbour(this);
    }
    else
    {
        pressed = true;
        update();
        QGraphicsItem::mousePressEvent(event);
    }
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        pressed = false;
        update();
        QGraphicsItem::mousePressEvent(event);
    }
}

double Node::getX() const
{
    return posX;
}

double Node::getY() const
{
    return posY;
}

unsigned Node::getNodeNumber() const
{
    return nodeNumber;
}
