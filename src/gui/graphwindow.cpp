#include "graphwindow.hpp"
#include "ui_graphwindow.h"
#include "../backend/graphalgorithm.hpp"
#include "../backend/bfs.hpp"
#include "../backend/graphalgorithmexecutorthread.hpp"
#include "../backend/graphalgorithmdrawingthread.hpp"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    this->resize(this->width() * 1.3, this->height() * 1.3);

    drawGraph = new DrawGraph(this);
    setCentralWidget(drawGraph);

    connect(drawGraph, SIGNAL(doneDrawingGraph(Graph*)), this, SLOT(setGraph(Graph*)));
    connect(drawGraph, SIGNAL(doneDrawingGraph(Graph*)), this, SLOT(enableRightDockWindow()));
    createDockWindows();

    setWindowTitle(tr("Graph Window"));

    this->installEventFilter(this);

    slider = new QSlider(Qt::Horizontal, this);
    ui->toolBar->addWidget(slider);
    ui->toolBar->setMovable(false);
    ui->toolBar->setStyleSheet("QSlider::handle:horizontal {"
                               "background-color: #5599ff; "
                               "border-radius: 9px;"
                               "} ");

    animationSetup();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::pushButtonReturn_clicked()
{
    deleteChildren();
    delete drawGraph;
    delete dockTop;
    delete dockRight;
    this->close();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
}

void GraphWindow::enableRightDockWindow()
{
    dockRight->setDisabled(false);
}

void GraphWindow::createDockWindows()
{
    createTopDockWindow();
    createRightDockWindow();
}

void GraphWindow::createTopDockWindow()
{
    dockTop = new QDockWidget(this);
    dockTop->setTitleBarWidget(new QWidget());

    pushButtonReturn = new QPushButton(" ", this);
    pushButtonReturn->setFixedWidth(buttonWidth);
    pushButtonReturn->setFixedHeight(buttonHeight);
    pushButtonReturn->setStyleSheet(QString("background-color: #5599ff"));

    connect(pushButtonReturn, &QPushButton::clicked, this, &GraphWindow::pushButtonReturn_clicked);
    dockTop->setWidget(pushButtonReturn);
    addDockWidget(Qt::TopDockWidgetArea, dockTop);
}

void GraphWindow::createRightDockWindow()
{
    dockRight = new QDockWidget(this);
    dockRight->setAttribute(Qt::WA_DeleteOnClose);
    dockRight->setTitleBarWidget(new QWidget()); // remove title bar
    dockRight->setDisabled(true);
    setAlgoGraphAtRightDockWindow();
}

void GraphWindow::changeRightDockWindow()
{
    if(isChild("algoGraph"))
    {
        name = algoGraph->getAlgoName();
        deleteChildren();
        setCodeGraphAtRightDockWindow();
    }
    else if(isChild("codeGraph"))
    {
        deleteChildren();
        setAlgoGraphAtRightDockWindow();
    }
}

void GraphWindow::setAlgoGraphAtRightDockWindow()
{
    algoGraph = new AlgoGraph(dockRight);
    algoGraph->setMinimumWidth(this->width() * 0.2);
    algoGraph->setObjectName("algoGraph");
    algoGraph->getAlgoName();
    dockRight->setWidget(algoGraph);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);
}

void GraphWindow::setCodeGraphAtRightDockWindow()
{
    codeGraph = new CodeGraph(dockRight);
    codeGraph->setMinimumWidth(this->width() * 0.35);
    codeGraph->setObjectName("codeGraph");
    dockRight->setWidget(codeGraph);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);
    codeGraph->setText(name);
}

bool GraphWindow::isChild(const QString &str)
{
    if(dockRight->findChild<QWidget *>(str))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GraphWindow::deleteChildren()
{
    auto children = dockRight->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (auto child : children)
    {
        delete child;
    }
}

void GraphWindow::animationSetup()
{
    group = new QSequentialAnimationGroup();

    hideAlgo = new QPropertyAnimation(dockRight, "maximumWidth");
    hideAlgo->setObjectName("hideAlgo");
    hideAlgo->setDuration(700);
    hideAlgo->setStartValue(algoGraph->width());
    hideAlgo->setEndValue(0);

    showCode = new QPropertyAnimation(dockRight, "maximumWidth");
    showCode->setObjectName("showCode");
    showCode->setDuration(500);
    showCode->setStartValue(0);
    showCode->setEndValue(algoGraph->width());

    group->addAnimation(hideAlgo);
    group->addAnimation(showCode);

    group2 = new QSequentialAnimationGroup();

    hideCode = new QPropertyAnimation(dockRight, "maximumWidth");
    hideCode->setObjectName("hideCode");
    hideCode->setDuration(500);
    hideCode->setStartValue(algoGraph->width());
    hideCode->setEndValue(0);

    showAlgo = new QPropertyAnimation(dockRight, "maximumWidth");
    showAlgo->setObjectName("showAlgo");
    showAlgo->setDuration(700);
    showAlgo->setStartValue(0);
    showAlgo->setEndValue(algoGraph->width());

    group2->addAnimation(hideCode);
    group2->addAnimation(showAlgo);
}

bool GraphWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(this == watched && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Alt)
        {
            if(num == 0)
            {
                group->blockSignals(true);
                group->start();
                group->blockSignals(false);
                connect(group, SIGNAL(currentAnimationChanged(QAbstractAnimation*)), this, SLOT(changeRightDockWindow()), Qt::UniqueConnection);
                num++;
                return true;
            }
            else
            {
                group2->blockSignals(true);
                group2->start();
                group2->blockSignals(false);
                connect(group2, SIGNAL(currentAnimationChanged(QAbstractAnimation*)), this, SLOT(changeRightDockWindow()), Qt::UniqueConnection);
                num--;
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}

void GraphWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int x = pushButtonReturn->pos().x();
    int y = pushButtonReturn->pos().y();
    int w = pushButtonReturn->width();
    int h = pushButtonReturn->height();

    QPoint point1(x + triangleWidth, y);
    QPoint point2(x, y + h/2);
    QPoint point3(x + triangleWidth, y + h);
    QPoint point4(x + triangleWidth, y + 3*h/4);
    QPoint point5(x + w, y + 3*h/4);
    QPoint point6(x + w, y + h/4);
    QPoint point7(x + triangleWidth, y + h/4);

    QPolygon polygon;
    polygon << point1 << point2 << point3 << point4 << point5 << point6 << point7;
    QRegion region(polygon);

    pushButtonReturn->setMask(region);
}

void GraphWindow::setGraph(Graph* g)
{
    this->currentGraph = g;
    BFS* algo = new BFS(this->currentGraph);
    auto thread = new GraphAlgorithmExecutorThread(algo);
    QObject::connect(thread, SIGNAL(graphAlgorithmFinished(GraphAlgorithm*)),
                     this, SLOT(graphAlgorithmFinished(GraphAlgorithm*)));

    QObject::connect(thread, &GraphAlgorithmExecutorThread::graphAlgorithmFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    thread->start();
}

void GraphWindow::graphAlgorithmFinished(GraphAlgorithm* algo)
{
    auto states = algo->getStates();
    auto thread = new GraphAlgorithmDrawingThread(states);
    QObject::connect(thread, &GraphAlgorithmDrawingThread::graphAlgorithmDrawingFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    delete algo;
    thread->start();
}

void GraphWindow::on_actionPlay_triggered()
{

}

void GraphWindow::on_actionPause_triggered()
{

}

void GraphWindow::on_actionStop_triggered()
{

}
