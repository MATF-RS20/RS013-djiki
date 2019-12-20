#ifndef EDGE_HPP
#define EDGE_HPP

#include "node.hpp"

class Edge : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Edge(Node* s, Node* e, int w, QWidget* p);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    Node* getStart() const;
    Node* getEnd() const;

    void animateEdge();
    void advance(int phase) override;

public Q_SLOTS:
    /* If user moves node edge needs to be redrawn, so this slot receives signal */
    void nodeMoved();

private:
    std::pair<QPointF, QPointF> getCurrentNodeCoords() const;
    void drawNodeWeight(QPainter* painter) const;

    Node* start;
    Node* end;

    int nodeWeight;
    bool animate;
    double animationStep;

    QWidget* parent;
};

#endif // EDGE_HPP
