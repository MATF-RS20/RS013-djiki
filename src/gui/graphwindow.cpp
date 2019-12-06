#include <QtWidgets>
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
