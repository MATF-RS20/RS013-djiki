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

#include <QSlider>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();
    const static int triangleWidth = 50;
    const static int buttonWidth = 150;
    const static int buttonHeight = 40;

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void pushButtonReturn_clicked();
    void enableRightDockWindow();
    void changeRightDockWindow();
    void setGraph(Graph *g);
    void graphAlgorithmFinished(GraphAlgorithm* algo);
    void on_actionPlay_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();

private:
    void createDockWindows();
    void createTopDockWindow();
    void createRightDockWindow();
    void setAlgoGraphAtRightDockWindow();
    void setCodeGraphAtRightDockWindow();
    bool isChild(const QString &str);
    void deleteChildren();
    void animationSetup();

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
    QSlider *slider;

    int num = 0;
    QString name;
};

#endif // GRAPHWINDOW_HPP
