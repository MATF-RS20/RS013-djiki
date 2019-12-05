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
    if (event->button() == Qt::LeftButton)
    {
        double x = event->x();
        double y = event->y();

        Node* newNode = new Node(x, y);
        nodes.push_back(newNode);

        QObject::connect(newNode,
                         &Node::drawNeighbour,
                         this,
                         &DrawGraph::drawEdge);

        scene->addItem(newNode);
    }
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
}

void DrawGraph::drawEdge(Node *node)
{
    selected.push_back(node);

    if (selected.size() < 2)
        return;
    else if (selected.size() > 2)
    {
        selected.clear();
        return;
    }

    Node* start = std::move(selected[0]);
    Node* end = std::move(selected[1]);
    selected.clear();

    if (start == end)
        return;

    QString title = "Enter weight for {" + QString::number(start->getNodeNumber())
                    + ", " + QString::number(end->getNodeNumber()) + "} edge.";

    bool ok;
    QString value = QInputDialog::getText(this, title, "Weight: ", QLineEdit::Normal,
                                          "0", &ok);

    if (ok && !value.isEmpty())
    {
        Edge* newEdge = new Edge(start, end, value.toInt());
        scene->addItem(newEdge);
    }
}
