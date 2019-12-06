#include "graphwindow.hpp"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::on_pushButton_clicked()
{
    this->close(); // or this->hide();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
}
