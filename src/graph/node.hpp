#ifndef NODE_HPP
#define NODE_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPropertyAnimation>

class Node : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Node(double x, double y);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    QPainterPath shape() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);
    bool isNeighbour(Node* n);
    void clearNeighbours();

    void animateNode();
    void stopAnimation();
    void advance(int phase) override;

    double getX() const;
    double getY() const;
    unsigned getNodeNumber() const;
    QVector<Node*> getNeighbours() const;

    static unsigned radius;
    static unsigned numberOfNodes;

Q_SIGNALS:
    /* When user starts drawing edge this signal is emitted */
    void drawNeighbour(Node* n);
    /* When node is moving this signal is emitted */
    void nodeMoved();
    /* After user deletes node this signal is emitted */
    void nodeDeleted(Node* n);

private:
    unsigned nodeNumber;

    double posX;
    double posY;

    QVector<Node*> neighbours;

    int animate;
    double step;
};

#endif // NODE_HPP
