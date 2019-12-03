#include "drawgraph.hpp"
#include "ui_drawgraph.h"

DrawGraph::DrawGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drawGraph)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void DrawGraph::mousePressEvent(QMouseEvent *event)
{
    double x = event->x();
    double y = event->y();

    Node* newNode = new Node(x - Node::radius/2, y - Node::radius/2);
    nodes.push_back(newNode);

    newNode->setPos(x, y);
    scene->addItem(newNode);
}

DrawGraph::~DrawGraph()
{
    for (auto& n : nodes)
        delete n;

    nodes.clear();

    delete scene;
    delete ui;
}
