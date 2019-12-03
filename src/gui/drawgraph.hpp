#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include <iostream>
#include <vector>

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
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

    virtual void mousePressEvent(QMouseEvent *event) override;

    ~DrawGraph() override;
private:
    Ui::drawGraph *ui;

    QVector<Node*> nodes;
    QGraphicsScene* scene;
};

#endif // DRAWGRAPH_HPP
