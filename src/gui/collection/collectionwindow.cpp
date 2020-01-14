#include "collectionwindow.hpp"
#include "ui_collectionwindow.h"
#include "../../backend/algorithmexecutorthread.hpp"
#include "../../backend/collections/collectionalgorithm.hpp"
#include "../../backend/collections/collectionalgorithmdrawingthread.hpp"
#include "ui_drawcollection.h"
#include "ui_algocollection.h"
#include "ui_codecollection.h"

QMutex CollectionWindow::playbackMutex;
QPair<int, unsigned> CollectionWindow::playback(1, 1000);

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

    connect(drawCollection, SIGNAL(doneDrawingCollection(Collection*)), this, SLOT(setCollection(Collection*)));
    connect(drawCollection, SIGNAL(doneDrawingCollection(Collection*)), this, SLOT(enableRightDockWindow()));

    setWindowTitle(tr("Collection Window"));

    toolBarSetup();
    createDockWindows();
    animationSetup();
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
    this->close();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
}

void CollectionWindow::enableRightDockWindow()
{
    dockRight->setDisabled(false);
}

void CollectionWindow::animateRightDockWindow()
{
    group->blockSignals(true);
    group->start();
    group->blockSignals(false);
    connect(group, SIGNAL(currentAnimationChanged(QAbstractAnimation*)), this, SLOT(changeRightDockWindow()), Qt::UniqueConnection);

    group2->blockSignals(true);
    group2->start();
    group2->blockSignals(false);
    connect(group2, SIGNAL(currentAnimationChanged(QAbstractAnimation*)), this, SLOT(changeRightDockWindow()), Qt::UniqueConnection);
}

void CollectionWindow::changeRightDockWindow()
{
    if(isChild("algoCollection"))
    {
        name = algoCollection->getAlgoName();

        algorithmInstance = algoCollection->getAlgorithmInstance();
        algorithmInstance->setCollection(*currentCollection);
        executeAlgorithm(algorithmInstance);

        deleteChildren();
        setCodeCollectionAtRightDockWindow();
    }
    else if(isChild("codeCollection"))
    {
        deleteChildren();
        setAlgoCollectionAtRightDockWindow();
    }
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
    disableThings();
    algoCollection = new AlgoCollection(dockRight);
    algoCollection->setMinimumWidth(this->width() * 0.27);
    algoCollection->setObjectName("algoCollection");
    algoCollection->getAlgoName();
    dockRight->setWidget(algoCollection);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);
}

void CollectionWindow::setCodeCollectionAtRightDockWindow()
{
    enableThings();
    codeCollection = new CodeCollection(dockRight);
//    codeCollection->setMinimumWidth(this->width() * 0.35);
    codeCollection->setObjectName("codeCollection");
    dockRight->setWidget(codeCollection);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);

    //    codeCollection->setText(name, algorithmInstance->getPseudoCodeHTML());
}

void CollectionWindow::enableThings()
{
    minus->setEnabled(true);
    plus->setEnabled(true);
    slider->setEnabled(true);
    ui->actionPlay->setEnabled(true);
    ui->actionPause->setEnabled(true);
    ui->actionStop->setEnabled(true);

    QMenu* menuEdit = ui->menubar->findChild<QMenu*>("menuEdit");
    QMenu* menuThemes = menuEdit->findChild<QMenu*>("menuChangeTheme");
    for(auto action : menuThemes->actions())
        action->setDisabled(true);
}

void CollectionWindow::disableThings()
{
    minus->setDisabled(true);
    plus->setDisabled(true);
    slider->setDisabled(true);
    ui->actionPlay->setDisabled(true);
    ui->actionPause->setDisabled(true);
    ui->actionStop->setDisabled(true);
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

void CollectionWindow::animationSetup()
{
    group = new QSequentialAnimationGroup();

    hideAlgo = new QPropertyAnimation(dockRight, "maximumWidth");
    hideAlgo->setObjectName("hideAlgo");
    hideAlgo->setDuration(700);
    hideAlgo->setStartValue(algoCollection->width());
    hideAlgo->setEndValue(0);

    showCode = new QPropertyAnimation(dockRight, "maximumWidth");
    showCode->setObjectName("showCode");
    showCode->setDuration(500);
    showCode->setStartValue(0);
    showCode->setEndValue(algoCollection->width());

    group->addAnimation(hideAlgo);
    group->addAnimation(showCode);

    group2 = new QSequentialAnimationGroup();

    hideCode = new QPropertyAnimation(dockRight, "maximumWidth");
    hideCode->setObjectName("hideCode");
    hideCode->setDuration(500);
    hideCode->setStartValue(algoCollection->width());
    hideCode->setEndValue(0);

    showAlgo = new QPropertyAnimation(dockRight, "maximumWidth");
    showAlgo->setObjectName("showAlgo");
    showAlgo->setDuration(700);
    showAlgo->setStartValue(0);
    showAlgo->setEndValue(algoCollection->width());

    group2->addAnimation(hideCode);
    group2->addAnimation(showAlgo);
}

void CollectionWindow::toolBarSetup()
{
    slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(1);
    slider->setMaximum(7);
    slider->setTickInterval(1);
    slider->setValue(4);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changePlaybackSpeed(int)));

    ui->toolBar->addWidget(slider);
    ui->toolBar->setMovable(false);
    ui->toolBar->setStyleSheet("QSlider::handle:horizontal {"
                               "background-color: #5599ff; "
                               "border-radius: 9px;"
                               "} ");

    QWidget *fontSizing = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;

    plus = new QPushButton("+", this);
    connect(plus, &QPushButton::clicked, this, &CollectionWindow::plus_clicked);
    minus = new QPushButton("-", this);
    connect(minus, &QPushButton::clicked, this, &CollectionWindow::minus_clicked);

    hLayout->setSpacing(5);
    hLayout->setMargin(0);
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(plus);
    hLayout->addWidget(minus);

    QLabel *lblFont = new QLabel("Pseudocode font size");
    lblFont->setAlignment(Qt::AlignCenter);

    vLayout->setSpacing(0);
    vLayout->setMargin(0);
    vLayout->addWidget(lblFont);
    vLayout->addLayout(hLayout);
    fontSizing->setLayout(vLayout);
    ui->toolBar->addWidget(fontSizing);
}

void CollectionWindow::clearStylesheets()
{
    this->setStyleSheet(QString());
    ui->toolBar->setStyleSheet(QString());
    Ui::AlgoCollection *uiAlgo = algoCollection->getUi();
    algoCollection->setStyleSheet(QString());
    uiAlgo->pushButtonBinarySearch->setStyleSheet(QString());
    uiAlgo->pushButtonBubbleSort->setStyleSheet(QString());
    uiAlgo->pushButtonInsertionSort->setStyleSheet(QString());
    uiAlgo->pushButtonMergeSort->setStyleSheet(QString());
    uiAlgo->pushButtonQuickSort->setStyleSheet(QString());
    uiAlgo->pushButtonSelectionSort->setStyleSheet(QString());
    pushButtonReturn->setStyleSheet(QString());
    Ui::DrawCollection *uiDraw = drawCollection->getUi();
    uiDraw->graphicsView->setStyleSheet(QString());
}

void CollectionWindow::setCollection(Collection* c)
{
    this->currentCollection = c;
}

Collection* CollectionWindow::getCollection()
{
    return currentCollection;
}

void CollectionWindow::executeAlgorithm(CollectionAlgorithm* algorithmInstance)
{
    auto thread = new AlgorithmExecutorThread(algorithmInstance);
    QObject::connect(thread, SIGNAL(algorithmExecutionFinished(Algorithm*)),
                     this, SLOT(startAlgorithmPlayback(Algorithm*)));

    QObject::connect(thread, &AlgorithmExecutorThread::algorithmExecutionFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    thread->start();
}


void CollectionWindow::setTheme(QFile *file)
{
    clearStylesheets();
    file->open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(file);
    this->setStyleSheet(stream.readAll());
    file->close();
}

void CollectionWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && event->screenPos() == QPoint(-1, -1))
    {
        animateRightDockWindow();
    }
}

void CollectionWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int x = pushButtonReturn->pos().x();
    int y = pushButtonReturn->pos().y();
    int w = pushButtonReturn->width();
    int h = pushButtonReturn->height();

    QPoint point1(x + triangleWidth, y);
    QPoint point2(x, y + h/2);
    QPoint point3(x + triangleWidth, y + h);
    QPoint point4(x + triangleWidth, y + 3*h/4);
    QPoint point5(x + w, y + 3*h/4);
    QPoint point6(x + w, y + h/4);
    QPoint point7(x + triangleWidth, y + h/4);

    QPolygon polygon;
    polygon << point1 << point2 << point3 << point4 << point5 << point6 << point7;
    QRegion region(polygon);

    pushButtonReturn->setMask(region);
}

void CollectionWindow::resizeEvent(QResizeEvent *event)
{
    if(isChild("codeCollection"))
        dockRight->resize(this->width() * 0.35, dockRight->height());
    else
        dockRight->resize(this->width() * 0.2, dockRight->height());
    QMainWindow::resizeEvent(event);
}

void CollectionWindow::on_actionSave_As_Image_triggered()
{
    QString filter = "PNG (*.png)";
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save As Image"), "",
                                                    tr("JPEG (*.jpg, *.jpeg);;PNG (*.png)"),
                                                    &filter,
                                                    QFileDialog::DontUseNativeDialog);

    if(fileName.isEmpty())
        return;
    if(!fileName.contains("."))
        fileName.append(QString(".png"));


    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QGraphicsProxyWidget* doneItem = drawCollection->doneItem;
    QGraphicsProxyWidget* helpItem = drawCollection->helpItem;
    QGraphicsProxyWidget* clearItem = drawCollection->clearItem;
    QGraphicsTextItem* directions = drawCollection->directions;
    Ui::DrawCollection* ui = drawCollection->getUi();

    doneItem->setVisible(false);
    helpItem->setVisible(false);
    clearItem->setVisible(false);

    bool returnDirections = false;
    if (directions->isVisible())
    {
        directions->setVisible(false);
        returnDirections = true;
    }

    ui->graphicsView->horizontalScrollBar()->hide();
    ui->graphicsView->verticalScrollBar()->hide();

    drawCollection->grab().save(&file);

    doneItem->setVisible(true);
    helpItem->setVisible(true);
    clearItem->setVisible(true);

    if (returnDirections)
        directions->setVisible(true);

    ui->graphicsView->horizontalScrollBar()->show();
    ui->graphicsView->verticalScrollBar()->show();
}

void CollectionWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void CollectionWindow::on_actionCombinear_triggered()
{
    QFile file(":/stylesheets/Combinear.qss");
    setTheme(&file);
}

void CollectionWindow::on_actionDarkeum_triggered()
{
    QFile file(":/stylesheets/Darkeum.qss");
    setTheme(&file);
}

void CollectionWindow::on_actionDiffnes_triggered()
{
    QFile file(":/stylesheets/Diffnes.qss");
    setTheme(&file);
}

void CollectionWindow::on_actionIntegrid_triggered()
{
    QFile file(":/stylesheets/Integrid.qss");
    setTheme(&file);
}

void CollectionWindow::on_actionMedize_triggered()
{
    QFile file(":/stylesheets/Medize.qss");
    setTheme(&file);
}

void CollectionWindow::startAlgorithmPlayback(Algorithm* algo)
{
    CollectionAlgorithm* algorithm = dynamic_cast<CollectionAlgorithm*>(algo);
    auto thread = new CollectionAlgorithmDrawingThread(algorithm, *currentCollection);
    QObject::connect(thread, SIGNAL(updateHTML(QString)),
                     this->codeCollection, SLOT(updateHTML(QString)));

    QObject::connect(thread, &CollectionAlgorithmDrawingThread::collectionAlgorithmDrawingFinished,
                     this, &CollectionWindow::playbackFinished,
                     Qt::QueuedConnection);

    QObject::connect(thread, &CollectionAlgorithmDrawingThread::collectionAlgorithmDrawingFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    QObject::connect(thread, &CollectionAlgorithmDrawingThread::updateLineInBox,
                     drawCollection, &DrawCollection::updateBox);

    thread->start();
    //TODO delete algorithm on return to main menu
}

void CollectionWindow::playbackFinished()
{
    playback.first = stop;
}

void CollectionWindow::on_actionPlay_triggered()
{
  if(playback.first == stop && isChild("codeCollection")){
      playback.first = play;
      startAlgorithmPlayback(algorithmInstance);
  }
  playbackMutex.try_lock();
  playback.first = play;
  playbackMutex.unlock();
}

void CollectionWindow::on_actionPause_triggered()
{
  playbackMutex.try_lock();
  playback.first = pausE;
}

void CollectionWindow::on_actionStop_triggered()
{

  playbackMutex.try_lock();
  playback.first = stop;
  playbackMutex.unlock();

  if(isChild("codeCollection"))
      codeCollection->setText(name, algorithmInstance->getPseudoCodeHTML());
}

void CollectionWindow::changePlaybackSpeed(int sliderValue)
{
    sliderValue -= slider->maximum() / 2 +1;
    sliderValue = 1000 * pow(2, -sliderValue);
    playback.second = sliderValue;
}


void CollectionWindow::plus_clicked()
{
    Ui::CodeCollection *ui = codeCollection->getUi();
    qreal z = ui->algoPseudocode->zoomFactor();
    if(z <= 1.7)
        ui->algoPseudocode->setZoomFactor(z + 0.1);
}

void CollectionWindow::minus_clicked()
{
    Ui::CodeCollection *ui = codeCollection->getUi();
    qreal z = ui->algoPseudocode->zoomFactor();
    if(z >= 1.1)
        ui->algoPseudocode->setZoomFactor(z - 0.1);
}
