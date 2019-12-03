#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include <iostream>
#include <vector>

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "mainwindow.hpp"
#include "../graph/node.hpp"

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

private:
    Ui::drawGraph *ui;

    QVector<Node*> nodes;
    QGraphicsScene* scene;

    int numOfSelected = 0;
};

#endif // DRAWGRAPH_HPP
