#ifndef NODE_HPP
#define NODE_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

class Node : public QGraphicsItem {
public:
    Node(double x, double y);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    static unsigned radius;
private:
    static unsigned numberOfNodes;

    unsigned nodeNumber;
    bool pressed;

    double posX;
    double posY;
};

#endif // NODE_HPP
