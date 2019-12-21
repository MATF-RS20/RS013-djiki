#include "drawgraph.hpp"
#include "ui_drawgraph.h"

#include <limits>

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsView>
#include <QInputDialog>
#include <QGraphicsProxyWidget>
#include <QPalette>
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
}

void DrawGraph::initializeScene()
{
    scene = new QGraphicsScene(0, 0, 2000, 1500, this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QFont font = QFont("Times", 12);
    QPushButton* clearBtn = createCheckBoxBtnOrLabel<QPushButton>("Clear", QPointF(width()-110, 40), font);
    QLabel* helpLabel = createCheckBoxBtnOrLabel<QLabel>("Help", QPointF(width()-80, 90), font);
    QCheckBox* doneBox = createCheckBoxBtnOrLabel<QCheckBox>("Done drawing graph", QPointF(20, 40), font);

    QObject::connect(clearBtn, &QPushButton::clicked,
                     this, &DrawGraph::onClearGraph);

    QObject::connect(doneBox, &QPushButton::clicked,
                     this, &DrawGraph::onDoneDrawing);

    helpLabel->setToolTip(drawDirections(font));
}

template <typename T>
T* DrawGraph::createCheckBoxBtnOrLabel(const QString& label, const QPointF& position, QFont font)
{
    T* btn = new T(label);

    btn->setFont(font);

    QGraphicsProxyWidget* item = scene->addWidget(btn);
    item->setPos(position);
    ui->graphicsView->centerOn(item);

    btn->setParent(this);

    return btn;
}

QString DrawGraph::drawDirections(QFont font)
{
    QString instructions = "Click anywhere to create nodes and click and drag to move them.\n\n"
                           "Right click on node to delete it.\n\n"
                           "Create edges by clicking on two nodes, holding control key.\n\n"
                           "After that enter node weight (Integer value or 'Inf').\n\n"
                           "Double click on edge to change it's weight.\n\n"
                           "Right click on edge to delete it.\n\n"
                           "When you finish click 'done adding nodes'.\n\n"
                           "You can start over from scratch by clicking Clear button.\n\n";

    font.setBold(true);
    directions = scene->addText(instructions, font);
    directions->setPos(QPointF(90, 120));

    directions->setDefaultTextColor("#5599ff");

    return instructions;
}

void DrawGraph::mousePressEvent(QMouseEvent* event)
{
    if (directions->isVisible())
        directions->setVisible(false);

    if (event->button() == Qt::LeftButton)
    {
        QPointF mapped = ui->graphicsView->mapToScene(event->pos());
        Node* newNode = new Node(mapped.x(), mapped.y());
        nodes.push_back(newNode);

        QObject::connect(newNode, &Node::drawNeighbour,
                         this, &DrawGraph::drawEdge);

        QObject::connect(newNode, &Node::nodeDeleted,
                         this, &DrawGraph::deleteFromNeighbours);

        scene->addItem(newNode);
    }
}

DrawGraph::~DrawGraph()
{
    onClearGraph();

    scene->clear();
    delete scene;
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

    if (start == end)
        return;

    if (start->isNeighbour(end) || end->isNeighbour(start))
        return;

    auto [status, value] = getWeightFromUser(start, end);
    if (!status)
        return;

    start->addNeighbour(end);

    Edge* newEdge = new Edge(start, end, value, this);

    QObject::connect(start, &Node::nodeMoved,
                     newEdge, &Edge::nodeMoved);

    QObject::connect(end, &Node::nodeMoved,
                     newEdge, &Edge::nodeMoved);

    edges.push_back(newEdge);
    scene->addItem(newEdge);

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
        scene->removeItem(n);
        delete n;
    }
    nodes.clear();
    selectedNodes.clear();

    for (const auto& e : edges)
    {
        scene->removeItem(e);
        delete e;
    }
    edges.clear();

    Node::numberOfNodes = 0;
}

void DrawGraph::onDoneDrawing()
{
    this->setEnabled(false);

    animationTimer = new QTimer(this);
    QObject::connect(animationTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    animationTimer->start(500);
    qDebug() << "TIMER STARTED!!! (stop it at the end of animations)";

    // Debug neighbours
    for (auto& n: nodes)
        for (auto& node: n->getNeighbours())
        {
            qDebug() << "NODE: " << n->getNodeNumber();
            qDebug() << node->getNodeNumber();
        }
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
            toRemove.push_back(i);
        }
    }

    auto it = std::crbegin(toRemove);
    while (it != std::crend(toRemove))
    {
        edges.remove(*it);
        it++;
    }

}
