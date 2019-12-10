#ifndef GRAPHWINDOW_HPP
#define GRAPHWINDOW_HPP

#include <QMainWindow>
#include <QPropertyAnimation>
#include "../graph/drawgraph.hpp"
#include "algograph.hpp"

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();

private slots:
    void on_pushButtonReturn_clicked();

private:
    void createDockWindows();

    Ui::GraphWindow *ui;
    DrawGraph *drawGraph;
    AlgoGraph *algoGraph;

    QPropertyAnimation *animate;

protected:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // GRAPHWINDOW_HPP
