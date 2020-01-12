#include "drawcollection.hpp"
#include "ui_drawcollection.h"

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

        collectionItems.push_back(newItem);

        ui->graphicsView->scene()->addItem(newItem);
    }
}

void DrawCollection::resizeEvent(QResizeEvent* event)
{
    // Move directions and buttons
}

DrawCollection::~DrawCollection()
{
    ui->graphicsView->scene()->clear();
    delete ui;
}
