#include "graphwindow.hpp"
#include "ui_graphwindow.h"
#include "../backend/bfs.hpp"
#include "../backend/graphalgorithmexecutorthread.hpp"
#include "../backend/graphalgorithmdrawingthread.hpp"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    drawGraph = new DrawGraph(this);
    setCentralWidget(drawGraph);
    connect(drawGraph, SIGNAL(doneDrawingGraph(Graph*)), this, SLOT(setGraph(Graph*)));

    createDockWindows();

    setWindowTitle(tr("Graph Window"));

    this->installEventFilter(this);

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
    this->close(); // or this->hide();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
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
    pushButtonReturn = new QPushButton();
    connect(pushButtonReturn, &QPushButton::clicked, this, &GraphWindow::pushButtonReturn_clicked);
    dockTop->setWidget(pushButtonReturn);
    addDockWidget(Qt::TopDockWidgetArea, dockTop);
}

void GraphWindow::createRightDockWindow()
{
    dockRight = new QDockWidget(this);
    dockRight->setAttribute(Qt::WA_DeleteOnClose);
    dockRight->setTitleBarWidget(new QWidget()); // remove title bar
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
    algoGraph->setObjectName("algoGraph");
    dockRight->setWidget(algoGraph);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);
}

void GraphWindow::setCodeGraphAtRightDockWindow()
{
    codeGraph = new CodeGraph(dockRight);
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
    hideAlgo->setDuration(2000);
    hideAlgo->setStartValue(algoGraph->width());
    hideAlgo->setEndValue(0);

    showCode = new QPropertyAnimation(dockRight, "maximumWidth");
    showCode->setObjectName("showCode");
    showCode->setDuration(2000);
    showCode->setStartValue(0);
    showCode->setEndValue(algoGraph->width());

    group->addAnimation(hideAlgo);
    group->addAnimation(showCode);

    group2 = new QSequentialAnimationGroup();

    hideCode = new QPropertyAnimation(dockRight, "maximumWidth");
    hideCode->setObjectName("hideCode");
    hideCode->setDuration(2000);
    hideCode->setStartValue(algoGraph->width());
    hideCode->setEndValue(0);

    showAlgo = new QPropertyAnimation(dockRight, "maximumWidth");
    showAlgo->setObjectName("showAlgo");
    showAlgo->setDuration(2000);
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
        if(keyEvent->key() == Qt::Key_Shift)
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

void GraphWindow::setGraph(Graph* g)
{
    this->currentGraph = g;
    BFS* algo = new BFS(this->currentGraph);
    auto thread = new GraphAlgorithmExecutorThread(algo);
    QObject::connect(thread, SIGNAL(graphAlgorithmFinished(BFS*)),
                     this, SLOT(graphAlgorithmFinished(BFS*)));

    QObject::connect(thread, &GraphAlgorithmExecutorThread::graphAlgorithmFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    thread->start();
}

void GraphWindow::graphAlgorithmFinished(BFS* algo)
{
    auto states = algo->getStates();
    auto thread = new GraphAlgorithmDrawingThread(states);
    QObject::connect(thread, &GraphAlgorithmDrawingThread::graphAlgorithmDrawingFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    delete algo;
    thread->start();
}
