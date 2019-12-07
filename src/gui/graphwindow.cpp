#include <QtWidgets>
#include "graphwindow.hpp"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    drawGraph = new DrawGraph;
    //drawGraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(drawGraph);

    createDockWindows();

    setWindowTitle(tr("Graph Window"));

    this->installEventFilter(this);

    animate = new QPropertyAnimation(algoGraph, "maximumWidth");
    animate->setDuration(1000);
    animate->setStartValue(300);
    animate->setEndValue(0);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::on_pushButtonReturn_clicked()
{
    this->close(); // or this->hide();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
}

void GraphWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Graph Algorithms"), this);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock->setTitleBarWidget(new QWidget()); // remove title bar
    algoGraph = new AlgoGraph(dock);
    dock->setWidget(algoGraph);
    addDockWidget(Qt::RightDockWidgetArea, dock, Qt::Vertical);
    //dock->toggleViewAction();
}

bool GraphWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(this == watched && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Space)
        {
            if(algoGraph->maximumWidth() == 0)
            {
                animate->setDirection(QAbstractAnimation::Backward);
                animate->start();
            }
            else if(algoGraph->maximumWidth() != 0)
            {
                animate->setDirection(QAbstractAnimation::Forward);
                animate->start();
            }
            return true;
        }
        else
            return false;
    }
    return false;
}
