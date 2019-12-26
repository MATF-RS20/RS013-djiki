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
#include "../backend/bfs.hpp"

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
    void changeRightDockWindow();
    void setGraph(Graph *g);
    void graphAlgorithmFinished(BFS* algo);

Q_SIGNALS:
    void nextAnimationInGroupStarted(QAbstractAnimation* group);

private:
    void createDockWindows();
    void createTopDockWindow();
    void createRightDockWindow();
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
    QSequentialAnimationGroup *group;
    QPropertyAnimation *hideAlgo;
    QPropertyAnimation *showCode;
    QSequentialAnimationGroup *group2;
    QPropertyAnimation *hideCode;
    QPropertyAnimation *showAlgo;

    int num = 0;

protected:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // GRAPHWINDOW_HPP
