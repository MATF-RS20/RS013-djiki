#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "item.hpp"

#include <QGraphicsLineItem>

class Connection : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Connection(Item* first, Item* second);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void advance(int phase) override;
    void animateConnection();

public Q_SLOTS:
    /* After user moves collection item this slot receives signal */
    void itemMoved();

private:
    Item* first;
    Item* second;
    std::pair<QPointF, QPointF> getCurrentItemCoords() const;

    bool animate;
    double currentStep;
};

#endif // CONNECTION_HPP
