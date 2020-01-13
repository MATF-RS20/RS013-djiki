#ifndef ITEM_HPP
#define ITEM_HPP

#include <QGraphicsItem>

class Item : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Item(qreal x, qreal y, int value, QWidget* parent);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void advance(int phase) override;
    void animateItem();
    void stopAnimation();

    qreal getItemPosX() const;
    qreal getItemPosY() const;
    int getItemValue() const;
    unsigned getItemIndex() const;
    void setItemValue(int newValue);

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
    int itemValue;

    bool animation;
    double currentStep;

    QWidget* parent;
};

#endif // ITEM_HPP
