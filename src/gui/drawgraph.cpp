#include "drawgraph.hpp"
#include "ui_drawgraph.h"

#include <limits>

#include <QPainter>
#include <QGraphicsView>
#include <QInputDialog>
#include <QGraphicsProxyWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QPalette>
#include <QLineF>
#include <QDebug>

DrawGraph::DrawGraph(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::drawGraph)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0, 0, width(), height(), this);
    ui->graphicsView->setScene(scene);
    initializeScene();
}

void DrawGraph::mousePressEvent(QMouseEvent *event)
{
    if (doneCreatingNodes)
        return;

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

void DrawGraph::initializeScene() const
{
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QGraphicsTextItem* addNodes = scene->addText("Click to add nodes: ",
                                                 QFont("Times", 16, QFont::Bold));
    addNodes->setPos(10, 5);
    addNodes->setDefaultTextColor(Qt::black);

    QCheckBox* box1 = createCheckBoxOrBtn<QCheckBox>("Done creating nodes: ", QPointF(20, 40));
    QCheckBox* box2 = createCheckBoxOrBtn<QCheckBox>("Done adding edges: ", QPointF(20, 70));
    QPushButton* btn = createCheckBoxOrBtn<QPushButton>("Clear", QPointF(width()-100, 40));

    QObject::connect(box1, &QCheckBox::clicked,
                     this, &DrawGraph::onDoneCreatingNodes);

    QObject::connect(box2, &QCheckBox::clicked,
                     this, &DrawGraph::onDoneAddingEdges);

    QObject::connect(btn, &QCheckBox::clicked,
                     this, &DrawGraph::onClearGraph);
}

template <typename T>
T* DrawGraph::createCheckBoxOrBtn(const QString& label, const QPointF& position) const
{
    T* btn = new T(label);

    btn->setStyleSheet("background-color:white");

    QPalette palette = btn->palette();
    palette.setColor(QPalette::WindowText, Qt::black);
    btn->setPalette(palette);

    btn->setFont(QFont("Times", 12));

    QGraphicsProxyWidget* item = scene->addWidget(btn);
    item->setPos(position);

    return btn;
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

    QString inputTitle = "Enter weight for {" + QString::number(start->getNodeNumber())
                    + ", " + QString::number(end->getNodeNumber()) + "} edge: ";

    bool status;
    QString enteredValue = QInputDialog::getText(this, "Enter", inputTitle,
                                                 QLineEdit::Normal, "0", &status);

    if (status && !enteredValue.isEmpty())
    {
        int intValue = enteredValue == "Inf" ?
                       std::numeric_limits<int>::max() :
                       enteredValue.toInt();

        start->addNeighbour(end);
        end->addNeighbour(start);

        Edge* newEdge = new Edge(start, end, intValue);
        scene->addItem(newEdge);
    }
}

void DrawGraph::onDoneCreatingNodes()
{
    for (auto& n : nodes)
        n->setFlag(QGraphicsItem::ItemIsMovable, false);

    doneCreatingNodes = true;
}

void DrawGraph::onDoneAddingEdges()
{
    this->setDisabled(true);
}

void DrawGraph::onClearGraph()
{
    for (const auto& n : nodes)
    {
        n->setVisible(false);
        delete n;
    }

    nodes.clear();

    for (const auto& s : selectedNodes)
        delete s;

    selectedNodes.clear();

    Node::numberOfNodes = 0;
    doneCreatingNodes = false;
}
