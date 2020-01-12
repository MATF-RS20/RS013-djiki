#ifndef ITEM_HPP
#define ITEM_HPP

#include <QGraphicsItem>

class Item : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Item(double x, double y);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    static unsigned itemHeight;
    static unsigned itemWidth;

private:
    double itemPosX;
    double itemPosY;
};

#endif // ITEM_HPP
