#ifndef DRAWCOLLECTION_HPP
#define DRAWCOLLECTION_HPP

#include "item.hpp"

#include <QWidget>

namespace Ui {
class DrawCollection;
}

class DrawCollection : public QWidget
{
    Q_OBJECT

public:
    explicit DrawCollection(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    ~DrawCollection() override;

private:
    Ui::DrawCollection *ui;
    void initializeScene();
    std::pair<qreal, qreal> getWindowSize() const;

    template <typename T>
    QGraphicsProxyWidget* createCheckBoxBtnOrLabel(const QString& label, const QPointF& position, QFont font);

    QVector<Item*> collectionItems;
};

#endif // DRAWCOLLECTION_HPP
