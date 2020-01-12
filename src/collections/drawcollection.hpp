#ifndef DRAWCOLLECTION_HPP
#define DRAWCOLLECTION_HPP

#include "item.hpp"
#include "connection.hpp"

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

public Q_SLOTS:
    void deleteItemFromCollection(Item* item);

private:
    Ui::DrawCollection *ui;
    void initializeScene();
    std::pair<qreal, qreal> getWindowSize() const;

    template <typename T>
    QGraphicsProxyWidget* createCheckBoxBtnOrLabel(const QString& label, const QPointF& position, QFont font);

    QVector<Item*> collectionItems;
    QVector<Connection*> connections;
};

#endif // DRAWCOLLECTION_HPP
