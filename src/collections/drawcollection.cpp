#include "drawcollection.hpp"
#include "ui_drawcollection.h"

#include "connection.hpp"

#include <QScreen>
#include <QMouseEvent>
#include <QDebug>

DrawCollection::DrawCollection(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DrawCollection)
{
    ui->setupUi(this);
    initializeScene();
}

void DrawCollection::initializeScene()
{
    std::pair<qreal, qreal> screenSize = getWindowSize();
    QGraphicsScene* scene = new QGraphicsScene(0, 0,
                                               screenSize.first, screenSize.second,
                                               this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

std::pair<qreal, qreal> DrawCollection::getWindowSize() const
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width();
    int height = screenGeometry.height();

    return std::make_pair<qreal, qreal>(width, height);
}

template<typename T>
QGraphicsProxyWidget* DrawCollection::createCheckBoxBtnOrLabel(const QString &label, const QPointF &position, QFont font)
{
    // TODO
}

void DrawCollection::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        QPointF mapped = ui->graphicsView->mapToScene(event->pos());

        Item* newItem = new Item(mapped.x(), mapped.y());

        QObject::connect(newItem, &Item::itemDeleted,
                         this, &DrawCollection::deleteItemFromCollection);

        ui->graphicsView->scene()->addItem(newItem);

        collectionItems.push_back(newItem);

        int n = collectionItems.size();
        if (n < 2)
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

void DrawCollection::resizeEvent(QResizeEvent* event)
{
    // Move directions and buttons
}

DrawCollection::~DrawCollection()
{
    for (auto& i: collectionItems)
        delete i;

    for (auto& c: connections)
        delete c;

    ui->graphicsView->scene()->clear();
    delete ui;
}

void DrawCollection::deleteItemFromCollection(Item *item)
{
    if (connections.size() > 0)
    {
        Connection* last = connections.last();
        connections.pop_back();
        last->removeFromScene();
        last->deleteLater();
    }

    collectionItems.pop_back();
    item->deleteLater();
}
