#include "drawcollection.hpp"
#include "ui_drawcollection.h"

#include "connection.hpp"

#include <QScreen>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QDebug>

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
    std::pair<qreal, qreal> screenSize = getWindowSize();
    QGraphicsScene* scene = new QGraphicsScene(0, 0,
                                               screenSize.first, screenSize.second,
                                               this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QFont font = QFont("Times", 12);

    clearItem = createCheckBoxBtnOrLabel<QPushButton>("Clear", QPointF(width()-130, 20), font);
    helpItem = createCheckBoxBtnOrLabel<QLabel>("Help", QPointF(width()-100, 70), font);
    doneItem = createCheckBoxBtnOrLabel<QCheckBox>("Done drawing collection", QPointF(20, 20), font);

    QPushButton* clearBtn = static_cast<QPushButton*>(clearItem->widget());
    QLabel* helpLabel = static_cast<QLabel*>(helpItem->widget());
    QCheckBox* doneBox = static_cast<QCheckBox*>(doneItem->widget());

    QObject::connect(clearBtn, &QPushButton::clicked,
                     this, &DrawCollection::onClearConnection);

    QObject::connect(doneBox, &QPushButton::clicked,
                     this, &DrawCollection::onDoneDrawing);

    helpLabel->setToolTip(drawDirections(font));
}

std::pair<qreal, qreal> DrawCollection::getWindowSize() const
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width();
    int height = screenGeometry.height();

    return std::make_pair<qreal, qreal>(width, height);
}

QString DrawCollection::drawDirections(QFont font)
{
    QString instructions = "Click anywhere to create items.\n\n"
                           "Click on and drag item to move it.\n\n"
                           "Right click on item to delete it (you can delete only last item).\n\n"
                           "When you finish click 'Done drawing collection'.\n\n"
                           "You can start over from scratch by clicking Clear button.\n\n";

    font.setBold(true);
    directions = ui->graphicsView->scene()->addText(instructions, font);
    qreal textWidth = directions->boundingRect().width();
    qreal textHeight = directions->boundingRect().height();
    directions->setPos(QPointF(width()/2 - textWidth/2, height()/2 - textHeight/2 + 50));

    directions->setDefaultTextColor("#5599ff");

    return instructions;
}

template<typename T>
QGraphicsProxyWidget* DrawCollection::createCheckBoxBtnOrLabel(const QString &label, const QPointF &position, QFont font)
{
    T* btn = new T(label);

    btn->setFont(font);

    QGraphicsProxyWidget* item = ui->graphicsView->scene()->addWidget(btn);
    item->setPos(position);
    ui->graphicsView->centerOn(item);

    btn->setParent(this);

    return item;
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

void DrawCollection::resizeEvent(QResizeEvent*)
{
    clearItem->setPos(QPointF(width()-130, 20));
    helpItem->setPos(QPointF(width()-100, 70));

    int x = (width() - 600) / 200;
    QFont font("Times", 12+x);
    directions->setFont(font);

    qreal textWidth = directions->boundingRect().width();
    qreal textHeight = directions->boundingRect().height();
    directions->setPos(QPointF(width()/2 - textWidth/2, height()/2 - textHeight/2 + 50));
}

DrawCollection::~DrawCollection()
{
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
}

void DrawCollection::onClearConnection()
{
    if (directions->isVisible())
        directions->setVisible(false);

    for (auto& c: connections)
    {
        c->removeFromScene();
        delete c;
    }
    connections.clear();

    for (auto& i: collectionItems)
    {
        ui->graphicsView->scene()->removeItem(i);
        delete i;
    }
    collectionItems.clear();

    Item::index = 0;
}
