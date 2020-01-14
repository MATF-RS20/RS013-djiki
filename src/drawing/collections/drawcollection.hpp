#ifndef DRAWCOLLECTION_HPP
#define DRAWCOLLECTION_HPP

#include "item.hpp"
#include "connection.hpp"
#include "collection.hpp"

#include <QWidget>
#include <QTimer>

namespace Ui {
class DrawCollection;
}

class DrawCollection : public QWidget
{
    Q_OBJECT

public:
    explicit DrawCollection(QWidget* parent = nullptr);

    void mousePressEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    Ui::DrawCollection* getUi() const;
    QTimer* getAnimationTimer() const;

    QGraphicsProxyWidget* clearItem;
    QGraphicsProxyWidget* helpItem;
    QGraphicsProxyWidget* doneItem;
    QGraphicsProxyWidget* codeItem;
    QGraphicsTextItem* directions;

    ~DrawCollection() override;

public Q_SLOTS:
    /* After user deletes last drawn item this slot receives signal */
    void deleteItemFromCollection(Item* item);

    /* After user clicks 'Done drawing collection' this slot receives signal */
    void onDoneDrawing();
    /* After uses clicks 'Clear' button this slot receives signal */
    void onClearCollection();

    /* This slot receives active line to be drawn */
    void updateBox(QString line);

Q_SIGNALS:
    void doneDrawingCollection(Collection *c);

private:
    Ui::DrawCollection* ui;
    void initializeScene();

    bool finished;  // used to disable creating new item on click after drawing is finished

    QVector<Item*> collectionItems;
    QVector<Connection*> connections;

    QTimer* animationTimer;

    QString activeLine;
    QString& cleanPseudocodeLine(QString& line);
};

#endif // DRAWCOLLECTION_HPP
