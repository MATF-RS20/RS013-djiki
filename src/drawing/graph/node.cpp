#include "node.hpp"

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

unsigned Node::numberOfNodes = 0;
unsigned Node::radius = 20;
QStack<unsigned> Node::deletedNumbers;

Node::Node(double x, double y)
    : nodePosX(x)
    , nodePosY(y)
{
    if (deletedNumbers.empty())
        nodeNumber = numberOfNodes++;
    else
    {
        nodeNumber = deletedNumbers.pop();
    }

    animation = 0;
    currentStep = 0;

    setZValue(10);
    setFlag(ItemIsMovable);
}

QRectF Node::boundingRect() const
{
    return QRectF(nodePosX, nodePosY, radius*1.5, radius*1.5);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPen pen;

    if (!animation)
        pen.setColor("#0e5a77");
    else
    {
        QColor color;
        color.setRedF(currentStep);
        pen.setColor(color);
    }

    pen.setWidth(3);
    painter->setPen(pen);

    QBrush brush(Qt::white);
    painter->setBrush(brush);

    QRectF rect = boundingRect();
    painter->drawEllipse(rect);

    painter->setFont(QFont("Times", 16, QFont::Bold));
    painter->drawText(rect, Qt::AlignCenter, QString::number(nodeNumber));
}

QPainterPath Node::shape() const
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(boundingRect());
    QPainterPath path = item->shape();
    delete item;

    return path;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        scene()->removeItem(this);
        deletedNumbers.push_back(nodeNumber);
        emit nodeDeleted(this);
    }
    else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        emit drawNeighbour(this);
    }
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);
    emit nodeMoved();
}

void Node::addNeighbour(Node* neighbour)
{
    neighbours.push_back(neighbour);
}

void Node::removeNeighbour(Node* neighbour)
{
    if (!isNeighbour(neighbour))
        return;

    auto position = std::find(std::begin(neighbours), std::end(neighbours), neighbour);
    neighbours.erase(position);
}

bool Node::isNeighbour(Node* n)
{
    if (std::find(std::cbegin(neighbours), std::cend(neighbours), n) != std::cend(neighbours))
        return true;

    return false;
}

void Node::clearNeighbours()
{
    neighbours.clear();
}

void Node::animateNode()
{
    animation = 1;
}

void Node::stopAnimation()
{
    animation = 0;
}

void Node::advance(int phase)
{
    /* This function is called twice for every item,
       first time with phase = 0, indicating that
       items are about to advance, and then all items
       advance with phase = 1 */
    if (!phase || !animation)
        return;

    currentStep += animation*0.1;

    if (currentStep > 1)
    {
        animation = -1;
        currentStep += animation*0.1;
    }

    if (currentStep < 0)
    {
        animation = 1;
        currentStep += animation*0.1;
    }

    update();
}

double Node::getX() const
{
    return nodePosX;
}

double Node::getY() const
{
    return nodePosY;
}

unsigned Node::getNodeNumber() const
{
    return nodeNumber;
}

QVector<Node*> Node::getNeighbours() const
{
    return neighbours;
}
