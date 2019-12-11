#include "graphwindow.hpp"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    drawGraph = new DrawGraph;
    setCentralWidget(drawGraph);

    createDockWindows();

    setWindowTitle(tr("Graph Window"));

    this->installEventFilter(this);

    animateRightDockWindow = new QPropertyAnimation(dockRight, "maximumWidth");
    animateRightDockWindow->setDuration(1000);
    animateRightDockWindow->setStartValue(algoGraph->width());
    animateRightDockWindow->setEndValue(0);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::pushButtonReturn_clicked()
{
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
        deleteChildren();
        setCodeGraphAtRightDockWindow();
    }
    else
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

bool GraphWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(this == watched && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Shift)
        {
            if(dockRight->maximumWidth() == 0)
            {
                changeRightDockWindow();
                animateRightDockWindow->setDirection(QAbstractAnimation::Backward);
                animateRightDockWindow->start();
            }
            else if(dockRight->maximumWidth() != 0)
            {
                animateRightDockWindow->setDirection(QAbstractAnimation::Forward);
                animateRightDockWindow->start();
            }
            return true;
        }
        else
            return false;
    }
    return false;
}
