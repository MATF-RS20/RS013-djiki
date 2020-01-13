#ifndef GRAPHWINDOW_HPP
#define GRAPHWINDOW_HPP

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QtWidgets>
#include <QSlider>
#include "../../drawing/graph/drawgraph.hpp"
#include "algograph.hpp"
#include "codegraph.hpp"
#include "../../drawing/graph/graph.hpp"
#include "../../backend/graphs/graphalgorithm.hpp"

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
    Graph* getGraph();
    static QPair<int, unsigned> playback;
    static QMutex playbackMutex;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event);

private slots:
    void pushButtonReturn_clicked();
    void enableRightDockWindow();
    void animateRightDockWindow();
    void changeRightDockWindow();
    void setGraph(Graph *g);
    void startAlgorithmPlayback(Algorithm* algo);
    void on_actionPlay_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();
    void changePlaybackSpeed(int);
    void playbackFinished();
    void on_actionSave_As_Image_triggered();
    void on_actionExit_triggered();
    void on_actionDiffnes_triggered();
    void on_actionCombinear_triggered();
    void on_actionDarkeum_triggered();
    void on_actionIntegrid_triggered();
    void on_actionMedize_triggered();
    void plus_clicked();
    void minus_clicked();

private:
    void createDockWindows();
    void createTopDockWindow();
    void createRightDockWindow();
    void setAlgoGraphAtRightDockWindow();
    void setCodeGraphAtRightDockWindow();
    bool isChild(const QString &str);
    void deleteChildren();
    void animationSetup();
    void toolBarSetup();
    void executeAlgorithm(GraphAlgorithm* algorithmInstance);
    void clearStylesheets();
    void setTheme(QFile *file);

    Ui::GraphWindow *ui;
    DrawGraph *drawGraph;
    AlgoGraph *algoGraph;
    CodeGraph *codeGraph;
    Graph *currentGraph;
    GraphAlgorithm* algorithmInstance;

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
    QPushButton *plus;
    QPushButton *minus;
    QString name;
};

enum playbackSettings
{
    play,
    pause,
    stop
};

#endif // GRAPHWINDOW_HPP
