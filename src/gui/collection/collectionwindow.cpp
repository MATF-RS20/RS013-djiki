#include <QtWidgets>
#include "collectionwindow.hpp"
#include "ui_collectionwindow.h"

CollectionWindow::CollectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CollectionWindow)
{
    ui->setupUi(this);
    this->resize(this->width() * 1.3, this->height() * 1.3);
    this->setStyleSheet("background-color: rgb(13, 13, 23); "
                        "color: rgb(239, 235, 231);");

    drawCollection = new DrawCollection(this);
    setCentralWidget(drawCollection);

//    connect(drawCollection, SIGNAL(doneDrawingCollection(Collection*)), this, SLOT(setCollection(Collection*)));
//    connect(drawCollection, SIGNAL(doneDrawingCollection(Collection*)), this, SLOT(enableRightDockWindow()));
    createDockWindows();

    setWindowTitle(tr("Collection Window"));
}

CollectionWindow::~CollectionWindow()
{
    delete ui;
}

void CollectionWindow::pushButtonReturn_clicked()
{
    deleteChildren();
    delete drawCollection;
    delete dockTop;
    delete dockRight;
    this->close(); // or this->hide();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
}

void CollectionWindow::createDockWindows()
{
    createTopDockWindow();
    createRightDockWindow();
}

void CollectionWindow::createTopDockWindow()
{
    dockTop = new QDockWidget(this);
    dockTop->setTitleBarWidget(new QWidget());

    pushButtonReturn = new QPushButton(" ", this);
    pushButtonReturn->setFixedWidth(buttonWidth);
    pushButtonReturn->setFixedHeight(buttonHeight);
    pushButtonReturn->setStyleSheet(QString("background-color: #5599ff"));

    connect(pushButtonReturn, &QPushButton::clicked, this, &CollectionWindow::pushButtonReturn_clicked);
    dockTop->setWidget(pushButtonReturn);
    addDockWidget(Qt::TopDockWidgetArea, dockTop);
}

void CollectionWindow::createRightDockWindow()
{
    dockRight = new QDockWidget(this);
    dockRight->setAttribute(Qt::WA_DeleteOnClose);
    dockRight->setTitleBarWidget(new QWidget()); // remove title bar
    dockRight->setDisabled(true);
    setAlgoCollectionAtRightDockWindow();
}

void CollectionWindow::setAlgoCollectionAtRightDockWindow()
{
    algoCollection = new AlgoCollection(dockRight);
    algoCollection->setMinimumWidth(this->width() * 0.27);
    algoCollection->setObjectName("algoCollection");
    algoCollection->getAlgoName();
    dockRight->setWidget(algoCollection);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);
}

void CollectionWindow::setCodeCollectionAtRightDockWindow()
{
    codeCollection = new CodeCollection(dockRight);
    codeCollection->setMinimumWidth(this->width() * 0.35);
    codeCollection->setObjectName("codeCollection");
    dockRight->setWidget(codeCollection);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);
    //    codeCollection->setText(name, algorithmInstance->getPseudoCodeHTML());
}

bool CollectionWindow::isChild(const QString &str)
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

void CollectionWindow::deleteChildren()
{
    auto children = dockRight->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);
    for (auto child : children)
    {
        delete child;
    }
}
