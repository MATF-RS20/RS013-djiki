#ifndef DRAWING_HPP
#define DRAWING_HPP

#include "graph/node.hpp"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>

class Drawing
{
public:
    static std::pair<qreal, qreal> getWindowSize();
    static void setScene(QGraphicsView* view, QWidget* parent);

    template <typename T>
    static QGraphicsProxyWidget* createBoxBtnOrLabel(QGraphicsView* view, const QString& label, const QPointF& position, QWidget* parent)
    {
        T* btn = new T(label);

        btn->setFont(font);

        QGraphicsProxyWidget* item = view->scene()->addWidget(btn);
        item->setPos(position);
        view->centerOn(item);

        btn->setParent(parent);

        return item;
    }

    static QGraphicsTextItem* drawDirections(QGraphicsView* view, QString instructions);

    template <typename T>
    static void resizeDrawingWidget(T* widget)
    {
        int width = widget->width();
        int height = widget->height();

        widget->clearItem->setPos(QPointF(width-130, 20));
        widget->helpItem->setPos(QPointF(width-100, 70));

        int x = (width - 600) / 200;
        QFont font("Times", 12+x);
        widget->directions->setFont(font);

        qreal textWidth = widget->directions->boundingRect().width();
        qreal textHeight = widget->directions->boundingRect().height();
        widget->directions->setPos(QPointF(width/2 - textWidth/2, height/2 - textHeight/2 + 50));
    }

    static std::pair<bool, int> getWeightFromUser(const Node* start, const Node* end, QWidget* parent);

    static QString splitLine(QString line);

    static QFont font;

private:
    Drawing() = delete;
};

#endif // DRAWING_HPP
