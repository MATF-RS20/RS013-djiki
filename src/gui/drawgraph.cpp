#include "drawgraph.hpp"
#include "ui_drawgraph.h"

DrawGraph::DrawGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drawGraph)
{
    ui->setupUi(this);

    int screen_height = QApplication::desktop()->height();
    int screen_width = QApplication::desktop()->width();

    m_canvas = QPixmap(screen_width, screen_height);

    ui->canvas->setScaledContents(true);
    ui->canvas->setPixmap(m_canvas.scaled(width(), height(), Qt::KeepAspectRatio));
}

void DrawGraph::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(&m_canvas);
    painter.setFont(QFont("Times", 12));
    painter.setPen(Qt::white);
    painter.drawText(QPoint(20, 20), "Create graph nodes (click to create)");

    if (m_x == 0 && m_y == 0)
        return;

    m_points.emplace_back(m_x, m_y);

    //TODO: Scale dots

    painter.drawEllipse(m_x - 10, m_y - 10, 20, 20);

    m_x = 0;
    m_y = 0;

    ui->canvas->setPixmap(m_canvas.scaled(width(), height(), Qt::KeepAspectRatio));
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

