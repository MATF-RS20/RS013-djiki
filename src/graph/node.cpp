#include "../graph/node.hpp"
#include <QApplication>
#include <QDebug>

unsigned Node::numberOfNodes = 0;
unsigned Node::radius = 20;

Node::Node(double x, double y)
    : posX(x)
    , posY(y)
{
    nodeNumber = numberOfNodes++;
    animate = 0;
    step = 0;

    setZValue(10);
    setFlag(ItemIsMovable);
}

QRectF Node::boundingRect() const
{
    return QRectF(posX, posY, radius*1.5, radius*1.5);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPen pen;

    if (!animate)
        pen.setColor("#0e5a77");
    else
    {
        QColor color;
        color.setRedF(step);
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

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        scene()->removeItem(this);
        emit nodeDeleted(this);
    }
    else if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        emit drawNeighbour(this);
    }
    else
    {
        update();
        QGraphicsItem::mousePressEvent(event);
        emit nodeMoved();
    }
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    emit nodeMoved();
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
    auto position = std::find(std::begin(neighbours), std::end(neighbours), neighbour);
    if (position != neighbours.end())
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

void Node::stopAnimation()
{
    animate = 0;
}

void Node::advance(int phase)
{
    if (!phase || !animate)
        return;

    step += animate*0.1;

    if (step > 1)
    {
        animate = -1;
        step += animate*0.1;
    }

    if (step < 0)
    {
        animate = 1;
        step += animate*0.1;
    }

    update();
}

void Node::animateNode()
{
    animate = 1;
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

QVector<Node*> Node::getNeighbours() const
{
    return neighbours;
}
