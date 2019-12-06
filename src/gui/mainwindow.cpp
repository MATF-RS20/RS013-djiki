#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    graphWindow = new GraphWindow(this);
    graphWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    collectionWindow = new CollectionWindow(this);
    collectionWindow->show();
}
