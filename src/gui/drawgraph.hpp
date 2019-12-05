#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include "mainwindow.hpp"
#include "../graph/node.hpp"
#include "../graph/edge.hpp"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QInputDialog>

namespace Ui {
class drawGraph;
}

class DrawGraph : public QWidget
{
    Q_OBJECT

public:
    explicit DrawGraph(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    ~DrawGraph() override;

public Q_SLOTS:
    void drawEdge(Node* node);

private:
    Ui::drawGraph *ui;

    QVector<Node*> nodes;
    QGraphicsScene* scene;

    QVector<Node*> selected;
};

#endif // DRAWGRAPH_HPP
