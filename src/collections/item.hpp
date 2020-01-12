#ifndef ITEM_HPP
#define ITEM_HPP

#include <QGraphicsItem>

class Item : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Item(qreal x, qreal y);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    qreal getItemPosX() const;
    qreal getItemPosY() const;

    static unsigned index;
    static int itemHeight;
    static int itemWidth;

Q_SIGNALS:
    void itemMoved();
    void itemDeleted(Item* item);

private:
    qreal itemPosX;
    qreal itemPosY;
    unsigned itemIndex;
};

#endif // ITEM_HPP
