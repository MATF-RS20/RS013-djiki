#include "drawgraph.hpp"
#include "ui_drawgraph.h"

DrawGraph::DrawGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drawGraph)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, width(), height(), this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QGraphicsTextItem *text = scene->addText("Click to add nodes: ", QFont("Times", 16, QFont::Bold));
    text->setPos(10, 5);
    text->setDefaultTextColor(QColor("black"));
}

void DrawGraph::mousePressEvent(QMouseEvent *event)
{
    double x = event->x();
    double y = event->y();

    Node* newNode = new Node(x, y);
    nodes.push_back(newNode);

    scene->addItem(newNode);
}

void DrawGraph::resizeEvent(QResizeEvent *)
{
    scene->setSceneRect(0, 0, width(), height());
}

DrawGraph::~DrawGraph()
{
    for (auto& n : nodes)
        delete n;

    nodes.clear();

    delete scene;
    delete ui;
}
