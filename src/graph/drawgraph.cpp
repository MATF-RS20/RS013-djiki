#include "drawgraph.hpp"
#include "ui_drawgraph.h"

#include <limits>
#include <iostream>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QInputDialog>
#include <QGraphicsProxyWidget>
#include <QScrollBar>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineF>
#include <QDebug>


DrawGraph::DrawGraph(QWidget* parent)
    : QWidget(parent)
      , ui(new Ui::drawGraph)
{
    ui->setupUi(this);

    initializeScene();
    finished = false;
}

void DrawGraph::initializeScene()
{
    QGraphicsScene* scene = new QGraphicsScene(0, 0, 2000, 1500, this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QFont font = QFont("Times", 12);

    clearItem = createCheckBoxBtnOrLabel<QPushButton>("Clear", QPointF(width()-130, 20), font);
    helpItem = createCheckBoxBtnOrLabel<QLabel>("Help", QPointF(width()-100, 70), font);
    doneItem = createCheckBoxBtnOrLabel<QCheckBox>("Done drawing graph", QPointF(20, 20), font);

    QPushButton* clearBtn = static_cast<QPushButton*>(clearItem->widget());
    QLabel* helpLabel = static_cast<QLabel*>(helpItem->widget());
    QCheckBox* doneBox = static_cast<QCheckBox*>(doneItem->widget());

    QObject::connect(clearBtn, &QPushButton::clicked,
                     this, &DrawGraph::onClearGraph);

    QObject::connect(doneBox, &QPushButton::clicked,
                     this, &DrawGraph::onDoneDrawing);

    helpLabel->setToolTip(drawDirections(font));
}

template <typename T>
QGraphicsProxyWidget* DrawGraph::createCheckBoxBtnOrLabel(const QString& label, const QPointF& position, QFont font)
{
    T* btn = new T(label);

    btn->setFont(font);

    QGraphicsProxyWidget* item = ui->graphicsView->scene()->addWidget(btn);
    item->setPos(position);
    ui->graphicsView->centerOn(item);

    btn->setParent(this);

    return item;
}

QString DrawGraph::drawDirections(QFont font)
{
    QString instructions = "Click anywhere to create nodes and click and drag to move them.\n\n"
                           "Right click on node to delete it.\n\n"
                           "Create directed edges by clicking on two nodes, holding control key.\n\n"
                           "After that enter node weight (Integer value or 'Inf').\n\n"
                           "Double click on edge to change it's weight.\n\n"
                           "Right click on edge to delete it.\n\n"
                           "When you finish click 'done adding nodes'.\n\n"
                           "You can start over from scratch by clicking Clear button.\n\n";

    font.setBold(true);
    directions = ui->graphicsView->scene()->addText(instructions, font);
    qreal textWidth = directions->boundingRect().width();
    qreal textHeight = directions->boundingRect().height();
    directions->setPos(QPointF(width()/2 - textWidth/2, height()/2 - textHeight/2 + 50));

    directions->setDefaultTextColor("#5599ff");

    return instructions;
}

void DrawGraph::mousePressEvent(QMouseEvent* event)
{
    if (directions->isVisible())
        directions->setVisible(false);

    if (event->buttons() == Qt::LeftButton && !finished)
    {
        QPointF mapped = ui->graphicsView->mapToScene(event->pos());
        Node* newNode = new Node(mapped.x(), mapped.y());
        nodes.push_back(newNode);

        QObject::connect(newNode, &Node::drawNeighbour,
                         this, &DrawGraph::drawEdge);

        QObject::connect(newNode, &Node::nodeDeleted,
                         this, &DrawGraph::deleteFromNeighbours);

        ui->graphicsView->scene()->addItem(newNode);
    }
}

void DrawGraph::resizeEvent(QResizeEvent *)
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

DrawGraph::~DrawGraph()
{
    onClearGraph();

    ui->graphicsView->scene()->clear();
}

void DrawGraph::drawEdge(Node* node)
{
    selectedNodes.push_back(node);

    if (selectedNodes.size() < 2)
        return;
    else if (selectedNodes.size() > 2)
    {
        selectedNodes.clear();
        return;
    }

    Node* start = std::move(selectedNodes[0]);
    Node* end = std::move(selectedNodes[1]);
    selectedNodes.clear();

    if (start->isNeighbour(end))
        return;

    auto [status, value] = getWeightFromUser(start, end);
    if (!status)
        return;

    bool curve = false;

    if (start == end)
        curve = true;

    if (end->isNeighbour(start))
    {
        for (auto& e : edges)
        {
            if (e->getStart() == end && e->getEnd() == start)
            {
                if (value != e->getEdgeWeight())
                    curve = true;

                break;
            }
        }
    }

    start->addNeighbour(end);

    Edge* newEdge = new Edge(start, end, value, curve, this);

    QObject::connect(start, &Node::nodeMoved,
                     newEdge, &Edge::nodeMoved);

    QObject::connect(end, &Node::nodeMoved,
                     newEdge, &Edge::nodeMoved);

    edges.push_back(newEdge);
    ui->graphicsView->scene()->addItem(newEdge);
}

std::pair<bool, int> DrawGraph::getWeightFromUser(const Node* start, const Node* end)
{
    QString inputLabel = "Enter weight for {" + QString::number(start->getNodeNumber())
                    + ", " + QString::number(end->getNodeNumber()) + "} edge: ";

    bool status;
    QString enteredValue = QInputDialog::getText(this, "Enter", inputLabel,
                                                 QLineEdit::Normal, "0", &status);

    return std::make_pair(status, enteredValue == "Inf" ? std::numeric_limits<int>::max()
                                                        : enteredValue.toInt());
}

void DrawGraph::onClearGraph()
{
    if (directions->isVisible())
        directions->setVisible(false);

    for (const auto& n : nodes)
    {
        ui->graphicsView->scene()->removeItem(n);
        delete n;
    }
    nodes.clear();
    selectedNodes.clear();

    for (const auto& e : edges)
    {
        ui->graphicsView->scene()->removeItem(e);
        delete e;
    }
    edges.clear();

    Node::numberOfNodes = 0;
    Node::deletedNumbers.clear();
}

void DrawGraph::onDoneDrawing()
{
    /* Disable scene, but leave scrollbars enabled ( before this->setEnabled(false) ) */
    finished = true;
    doneItem->setEnabled(false);
    clearItem->setEnabled(false);
    helpItem->setEnabled(false);

    for (auto& n: nodes)
        n->setEnabled(false);

    for (auto& e: edges)
        e->setEnabled(false);

    animationTimer = new QTimer(this);
    QObject::connect(animationTimer, &QTimer::timeout, ui->graphicsView->scene(), &QGraphicsScene::advance);
    animationTimer->start(500);
    qDebug() << "TIMER STARTED!!! (stop it at the end of animations)";

    Graph g = Graph(&nodes, &edges);
    emit doneDrawingGraph(&g);
}

void DrawGraph::deleteFromNeighbours(Node* n)
{
    int forRemoving = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i]->removeNeighbour(n);

        if (nodes[i] == n)
            forRemoving = i;
    }

    nodes.remove(forRemoving);

    QVector<int> toRemove;

    for (int i = 0; i < edges.size(); i++)
    {
        if (edges[i]->getStart() == n || edges[i]->getEnd() == n)
        {
            edges[i]->setVisible(false);
            edges[i]->deleteLater();
            toRemove.push_back(i);
        }
    }

    auto it = std::crbegin(toRemove);
    while (it != std::crend(toRemove))
    {
        edges.remove(*it);
        it++;
    }

    n->deleteLater();
}

void DrawGraph::removeEdge(Edge *e)
{
    auto it = std::find(std::begin(edges), std::end(edges), e);
    if (it != edges.end())
        edges.erase(it);

    e->deleteLater();
}
