#include "drawcollection.hpp"
#include "ui_drawcollection.h"

#include "connection.hpp"
#include "../drawing.hpp"

#include <QScreen>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

DrawCollection::DrawCollection(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DrawCollection)
{
    ui->setupUi(this);

    initializeScene();
    finished = false;
}

void DrawCollection::initializeScene()
{
    Drawing::setScene(ui->graphicsView, this);

    clearItem = Drawing::createBoxBtnOrLabel<QPushButton>(ui->graphicsView, "Clear", QPointF(width()-130, 20), this);
    helpItem = Drawing::createBoxBtnOrLabel<QLabel>(ui->graphicsView, "Help", QPointF(width()-100, 70), this);
    doneItem = Drawing::createBoxBtnOrLabel<QCheckBox>(ui->graphicsView, "Done drawing collection", QPointF(20, 20), this);

    QPushButton* clearBtn = static_cast<QPushButton*>(clearItem->widget());
    QLabel* helpLabel = static_cast<QLabel*>(helpItem->widget());
    QCheckBox* doneBox = static_cast<QCheckBox*>(doneItem->widget());

    QObject::connect(clearBtn, &QPushButton::clicked,
                     this, &DrawCollection::onClearCollection);

    QObject::connect(doneBox, &QPushButton::clicked,
                     this, &DrawCollection::onDoneDrawing);

    QString instructions = "Click anywhere to create items.\n\n"
                           "Click on and drag item to move it.\n\n"
                           "Right click on item to delete it (you can delete only last item).\n\n"
                           "When you finish click 'Done drawing collection'.\n\n"
                           "You can start over from scratch by clicking Clear button.\n\n";

    directions = Drawing::drawDirections(ui->graphicsView, instructions);
    helpLabel->setToolTip(instructions);
}

void DrawCollection::mousePressEvent(QMouseEvent* event)
{
    if (directions->isVisible())
        directions->setVisible(false);

    if (event->buttons() == Qt::LeftButton && !finished)
    {
        QPointF mapped = ui->graphicsView->mapToScene(event->pos());
        Item* newItem = new Item(mapped.x(), mapped.y());

        QObject::connect(newItem, &Item::itemDeleted,
                         this, &DrawCollection::deleteItemFromCollection);

        ui->graphicsView->scene()->addItem(newItem);
        collectionItems.push_back(newItem);

        int n = collectionItems.size();
        if (n < 2)  // Not enough items created to make connection
            return;

        Connection* newConnection = new Connection(collectionItems[n-2], newItem);
        connections.push_back(newConnection);

        QObject::connect(collectionItems[n-2], &Item::itemMoved,
                         newConnection, &Connection::itemMoved);

        QObject::connect(newItem, &Item::itemMoved,
                         newConnection, &Connection::itemMoved);

        ui->graphicsView->scene()->addItem(newConnection);
    }
}

void DrawCollection::resizeEvent(QResizeEvent*)
{
    Drawing::resizeDrawingWidget(this);
}

Ui::DrawCollection* DrawCollection::getUi() const
{
    return ui;
}

QTimer* DrawCollection::getAnimationTimer() const
{
    return animationTimer;
}

DrawCollection::~DrawCollection()
{
    ui->graphicsView->scene()->clear();

    delete ui;
}

void DrawCollection::deleteItemFromCollection(Item* item)
{
    if (connections.size() > 0)
    {
        Connection* last = connections.last();
        connections.pop_back();
        ui->graphicsView->scene()->removeItem(last);
        last->deleteLater();
    }

    collectionItems.pop_back();
    item->deleteLater();
}

void DrawCollection::onDoneDrawing()
{
    finished = true;
    doneItem->setEnabled(false);
    clearItem->setEnabled(false);
    helpItem->setEnabled(false);

    for (auto& c: connections)
        c->setEnabled(false);

    for (auto& i: collectionItems)
        i->setEnabled(false);

    animationTimer = new QTimer(this);
    QObject::connect(animationTimer, &QTimer::timeout, ui->graphicsView->scene(), &QGraphicsScene::advance);
    animationTimer->start(200);
}

void DrawCollection::onClearCollection()
{
    if (directions->isVisible())
        directions->setVisible(false);

    /* Delete all connections */
    for (auto& c: connections)
    {
        ui->graphicsView->scene()->removeItem(c);
        c->deleteLater();
    }
    connections.clear();

    /* Delete all items */
    for (auto& i: collectionItems)
    {
        ui->graphicsView->scene()->removeItem(i);
        i->deleteLater();
    }
    collectionItems.clear();

    Item::index = 0;
}
