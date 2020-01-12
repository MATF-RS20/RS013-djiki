#include "algograph.hpp"
#include "ui_algograph.h"

#include "../backend/bfs.hpp"

AlgoGraph::AlgoGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoGraph)
{
    ui->setupUi(this);
    ui->pushButtonAStar->setStyleSheet("background-color: rgb(85, 153, 255);");
}

AlgoGraph::~AlgoGraph()
{
    delete ui;
}

void AlgoGraph::on_pushButtonAStar_clicked()
{
    algoName = "A*";

    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoGraph::on_pushButtonDijkstra_clicked()
{
    algoName = "Dijkstra";

    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoGraph::on_pushButtonDFS_clicked()
{
    algoName = "DFS";

    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoGraph::on_pushButtonBFS_clicked()
{
    algoName = "BFS";
    algorithmInstance = new BFS();

    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoGraph::on_pushButtonFW_clicked()
{
    algoName = "FW";

    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoGraph::on_pushButtonAdd_clicked()
{
    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

QString AlgoGraph::getAlgoName()
{
    return AlgoGraph::algoName;
}

GraphAlgorithm* AlgoGraph::getAlgorithmInstance()
{
    return AlgoGraph::algorithmInstance;
}

Ui::AlgoGraph *AlgoGraph::getUi() const
{
    return ui;
}
