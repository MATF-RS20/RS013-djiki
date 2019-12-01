#include "drawgraph.hpp"
#include "ui_drawgraph.h"

DrawGraph::DrawGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawGraph)
{
    ui->setupUi(this);
}

void DrawGraph::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.setFont(QFont("Times", 12));
    painter.drawText(QPoint(20, 20), "Create graph nodes (click to create)");

    if (m_x == 0 && m_y == 0)
        return;

    m_points.emplace_back(m_x, m_y);

    painter.drawEllipse(m_x, m_y, 10, 10);

    m_x = 0;
    m_y = 0;

}

void DrawGraph::mousePressEvent(QMouseEvent *event)
{
    m_x = event->x();
    m_y = event->y();
    update();
}

DrawGraph::~DrawGraph()
{
    delete ui;
}
