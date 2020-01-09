#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(this->width() * 1.3, this->height() * 1.3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGraph_clicked()
{
    this->hide();
    graphWindow = new GraphWindow(this);
    graphWindow->show();
}

void MainWindow::on_pushButtonCollection_clicked()
{
    this->hide();
    collectionWindow = new CollectionWindow(this);
    collectionWindow->show();
}
