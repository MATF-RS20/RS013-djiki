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
    setFlag(ItemIsMovable);
}

QRectF Node::boundingRect() const
{
    return QRectF(posX, posY, radius*1.5, radius*1.5);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(nodeColor);
    pen.setWidth(3);

    painter->setPen(pen);

    QBrush brush(Qt::white);
    painter->setBrush(brush);

    QRectF rect = boundingRect();
    painter->drawEllipse(rect);

    // Debug boundingRect
//    pen.setWidth(1);
//    pen.setColor(Qt::red);
//    painter->setPen(pen);
//    painter->setBrush(QBrush());
//    painter->drawRect(rect);

    painter->setFont(QFont("Times", 16, QFont::Bold));
    painter->drawText(rect, Qt::AlignCenter, QString::number(nodeNumber));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        this->setVisible(false);
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
        emit moving();
    }
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
    emit moving();
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    emit moving();
}

void Node::addNeighbour(Node *neighbour)
{
    neighbours.push_back(neighbour);
}

void Node::removeNeighbour(Node *neighbour)
{
    auto position = std::find(neighbours.begin(), neighbours.end(), neighbour);
    if (position != neighbours.end())
    {
        neighbours.erase(position);
        qDebug() << "REMOVED " << neighbour->getNodeNumber() << "FROM " << nodeNumber;
    }
}

bool Node::isNeighbour(Node *n)
{
    if (std::find(neighbours.begin(), neighbours.end(), n) != neighbours.end())
        return true;

    return false;
}

void Node::clearNeighbours()
{
    neighbours.clear();
}

void Node::setNodeColor(QColor &color)
{
    nodeColor = color;
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

QVector<Node *> Node::getNeighbours() const
{
    return neighbours;
}
