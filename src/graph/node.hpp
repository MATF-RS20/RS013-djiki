#ifndef NODE_HPP
#define NODE_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

class Node : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Node(double x, double y);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);
    bool isNeighbour(Node* n);
    void clearNeighbours();
    void setNodeColor(QColor& color);

    double getX() const;
    double getY() const;
    unsigned getNodeNumber() const;
    QVector<Node*> getNeighbours() const;

    static unsigned radius;
    static unsigned numberOfNodes;

Q_SIGNALS:
    void drawNeighbour(Node* n);
    void moving();
    void nodeDeleted(Node* n);

private:
    unsigned nodeNumber;
    bool pressed;

    double posX;
    double posY;
    QColor nodeColor = "#0e5a77";

    QVector<Node*> neighbours;
};

#endif // NODE_HPP
