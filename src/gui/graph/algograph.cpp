#include "algograph.hpp"
#include "ui_algograph.h"

#include "../../backend/graphs/bfs.hpp"
#include "../../backend/graphs/dfs.hpp"
#include "../../backend/graphs/dijkstra.hpp"

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

void AlgoGraph::notifyParent()
{
    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);

    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoGraph::on_pushButtonDijkstra_clicked()
{
    algoName = "Dijkstra";
    algorithmInstance = new Dijkstra();
    notifyParent();
}

void AlgoGraph::on_pushButtonDFS_clicked()
{
    algoName = "DFS";
    algorithmInstance = new DFS();

    notifyParent();
}

void AlgoGraph::on_pushButtonBFS_clicked()
{
    algoName = "BFS";
    algorithmInstance = new BFS();

    notifyParent();
}

void AlgoGraph::on_pushButtonPrim_clicked()
{
    algoName = "Prim";

    notifyParent();
}
