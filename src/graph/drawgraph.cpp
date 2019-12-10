#include "drawgraph.hpp"
#include "ui_drawgraph.h"

#include <limits>

#include <QPainter>
#include <QGraphicsView>
#include <QInputDialog>
#include <QGraphicsProxyWidget>
#include <QPalette>
#include <QPushButton>
#include <QCheckBox>
#include <QLineF>
#include <QDebug>


DrawGraph::DrawGraph(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::drawGraph)
{
    ui->setupUi(this);

    initializeScene();
}

void DrawGraph::initializeScene()
{
    scene = new QGraphicsScene(0, 0, width(), height(), this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QPushButton* clearBtn = createCheckBoxOrBtn<QPushButton>("Clear", QPointF(width()-100, 40));
    QCheckBox* doneBox = createCheckBoxOrBtn<QCheckBox>("Done drawing graph", QPointF(20, 40));

    QObject::connect(clearBtn, &QPushButton::clicked,
                     this, &DrawGraph::onClearGraph);

    QObject::connect(doneBox, &QPushButton::clicked,
                     this, &DrawGraph::onDoneDrawing);

    drawDirections();
}

template <typename T>
T* DrawGraph::createCheckBoxOrBtn(const QString& label, const QPointF& position) const
{
    T* btn = new T(label);

    btn->setFont(QFont("Times", 12));

    QGraphicsProxyWidget* item = scene->addWidget(btn);
    item->setPos(position);

    return btn;
}

void DrawGraph::drawDirections()
{
    QString instructions = "Click anywhere to create nodes and click and drag to move them.\n\n"
                           "Right click on node to delete it.\n\n"
                           "Create edges by clicking on two nodes, holding control key.\n\n"
                           "After that enter node weight (Integer value or 'Inf').\n\n"
                           "Double click on edge to change it's weight.\n\n"
                           "Right click on edge to delete it.\n\n"
                           "When you finish click 'done adding nodes'.\n\n"
                           "You can start over from scratch by clicking Clear button.\n\n";

    directions = scene->addText(instructions, QFont("Times", 12, QFont::Bold));
    directions->setPos(QPointF(scene->width()/8, scene->height()/4));

    directions->setDefaultTextColor("#5599ff");
}

void DrawGraph::mousePressEvent(QMouseEvent *event)
{
    if (directions->isVisible())
        directions->setVisible(false);

    if (event->button() == Qt::LeftButton)
    {
        Node* newNode = new Node(event->x(), event->y());
        nodes.push_back(newNode);

        QObject::connect(newNode, &Node::drawNeighbour,
                         this, &DrawGraph::drawEdge);

        scene->addItem(newNode);
    }
}

void DrawGraph::resizeEvent(QResizeEvent *)
{
    scene->setSceneRect(0, 0, width(), height());
}

DrawGraph::~DrawGraph()
{
    onClearGraph();

    scene->clear();
    delete scene;
}

void DrawGraph::drawEdge(Node *node)
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

    int value = getWeightFromUser(start, end);

    start->addNeighbour(end);
    end->addNeighbour(start);

    Edge* newEdge = new Edge(start, end, value, this);

    QObject::connect(start, &Node::moving,
                     newEdge, &Edge::nodeMoved);

    QObject::connect(end, &Node::moving,
                     newEdge, &Edge::nodeMoved);

    edges.push_back(newEdge);
    scene->addItem(newEdge);

}

int DrawGraph::getWeightFromUser(const Node* start, const Node* end)
{
    QString inputLabel = "Enter weight for {" + QString::number(start->getNodeNumber())
                    + ", " + QString::number(end->getNodeNumber()) + "} edge: ";

    QString enteredValue = QInputDialog::getText(this, "Enter", inputLabel,
                                                 QLineEdit::Normal, "0");

    return enteredValue == "Inf" ?
           std::numeric_limits<int>::max() :
           enteredValue.toInt();
}

void DrawGraph::onClearGraph()
{
    if (directions->isVisible())
        directions->setVisible(false);

    for (const auto& n : nodes)
    {
        n->setVisible(false);
        delete n;
    }
    nodes.clear();

    for (const auto& s : selectedNodes)
        delete s;
    selectedNodes.clear();

    for (const auto& e : edges)
        delete e;
    edges.clear();

    Node::numberOfNodes = 0;
}

void DrawGraph::onDoneDrawing()
{
    this->setEnabled(false);
}

void DrawGraph::deleteFromNeighbours(Node *n)
{
    for (auto& node : nodes)
    {
        node->removeNeighbour(n);
    }
}
