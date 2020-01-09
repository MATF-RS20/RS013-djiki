#include <QtWidgets>
#include "collectionwindow.hpp"
#include "ui_collectionwindow.h"

CollectionWindow::CollectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CollectionWindow)
{
    ui->setupUi(this);
    this->resize(this->width() * 1.3, this->height() * 1.3);

    createDockWindows();
}

CollectionWindow::~CollectionWindow()
{
    delete ui;
}

void CollectionWindow::pushButtonReturn_clicked()
{
    this->close(); // or this->hide();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
}

void CollectionWindow::createDockWindows()
{
    QDockWidget *dockTop = new QDockWidget(this);
    dockTop->setTitleBarWidget(new QWidget());
    pushButtonReturn = new QPushButton();
    connect(pushButtonReturn, &QPushButton::clicked, this, &CollectionWindow::pushButtonReturn_clicked);
    dockTop->setWidget(pushButtonReturn);
    addDockWidget(Qt::TopDockWidgetArea, dockTop);
}
