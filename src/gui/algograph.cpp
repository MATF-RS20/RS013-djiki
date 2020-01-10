#include "algograph.hpp"
#include "ui_algograph.h"

#include "../backend/bfs.hpp"

AlgoGraph::AlgoGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoGraph)
{
    ui->setupUi(this);
}

AlgoGraph::~AlgoGraph()
{
    delete ui;
}

void AlgoGraph::on_pushButtonAStar_clicked()
{
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
    algoName = "A*";
}

void AlgoGraph::on_pushButtonDijkstra_clicked()
{
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
    algoName = "Dijkstra";
}

void AlgoGraph::on_pushButtonDFS_clicked()
{
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
    algoName = "DFS";
}

void AlgoGraph::on_pushButtonBFS_clicked()
{
    algoName = "BFS";
    algorithmInstance = new BFS();

    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoGraph::on_pushButtonFW_clicked()
{
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
    algoName = "FW";
}

void AlgoGraph::on_pushButtonAdd_clicked()
{
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Alt, Qt::NoModifier);
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
