#ifndef GRAPHWINDOW_HPP
#define GRAPHWINDOW_HPP

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QtWidgets>
#include "../graph/drawgraph.hpp"
#include "algograph.hpp"
#include "codegraph.hpp"
#include "../graph/graph.hpp"

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
    void pushButtonReturn_clicked();
    void setGraph(Graph *g);

private:
    void createDockWindows();
    void createTopDockWindow();
    void createRightDockWindow();
    void changeRightDockWindow();
    void setAlgoGraphAtRightDockWindow();
    void setCodeGraphAtRightDockWindow();
    bool isChild(const QString &str);
    void deleteChildren();

    Ui::GraphWindow *ui;
    DrawGraph *drawGraph;
    AlgoGraph *algoGraph;
    CodeGraph *codeGraph;
    Graph *currentGraph;

    QDockWidget *dockRight;
    QDockWidget *dockTop;
    QPushButton *pushButtonReturn;

    QPropertyAnimation *animateRightDockWindow;
    QPropertyAnimation *animationShowCode;

protected:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // GRAPHWINDOW_HPP
