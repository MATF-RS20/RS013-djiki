#include "collectionwindow.hpp"
#include "ui_collectionwindow.h"

CollectionWindow::CollectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CollectionWindow)
{
    ui->setupUi(this);
}

CollectionWindow::~CollectionWindow()
{
    delete ui;
}
