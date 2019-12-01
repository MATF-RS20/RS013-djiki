#ifndef DRAWGRAPH_HPP
#define DRAWGRAPH_HPP

#include <iostream>
#include <vector>

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class DrawGraph;
}

class DrawGraph : public QWidget
{
    Q_OBJECT

public:
    explicit DrawGraph(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

    ~DrawGraph() override;
private:
    Ui::DrawGraph *ui;
    int m_x = 0;
    int m_y = 0;
    std::vector<std::pair<int, int>> m_points;
};

#endif // DRAWGRAPH_HPP
