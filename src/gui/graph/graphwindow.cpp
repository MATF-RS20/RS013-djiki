#include "graphwindow.hpp"
#include "ui_graphwindow.h"
#include "../../backend/algorithmexecutorthread.hpp"
#include "../../backend/graphs/graphalgorithm.hpp"
#include "../../backend/graphs/graphalgorithmdrawingthread.hpp"
#include "ui_drawgraph.h"
#include "ui_algograph.h"
#include "ui_codegraph.h"

QMutex GraphWindow::playbackMutex;
QPair<int, unsigned> GraphWindow::playback(play, 1000);

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
    this->resize(this->width() * 1.3, this->height() * 1.3);
    this->setStyleSheet("background-color: rgb(13, 13, 23); "
                        "color: rgb(239, 235, 231);");

    drawGraph = new DrawGraph(this);
    setCentralWidget(drawGraph);

    connect(drawGraph, SIGNAL(doneDrawingGraph(Graph*)), this, SLOT(setGraph(Graph*)));
    connect(drawGraph, SIGNAL(doneDrawingGraph(Graph*)), this, SLOT(enableRightDockWindow()));

    this->currentGraph = nullptr;
    this->algorithmInstance = nullptr;

    setWindowTitle(tr("Graph Window"));

    toolBarSetup();
    createDockWindows();
    animationSetup();
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::pushButtonReturn_clicked()
{
    playback.first = stop;
    GraphAlgorithmDrawingThread::threadAlive.lock();
    GraphAlgorithmDrawingThread::threadAlive.unlock();
    playbackMutex.tryLock();
    playback.first = play;
    playbackMutex.unlock();

    if(this->currentGraph)
        delete this->getGraph();
    if(this->algorithmInstance)
        delete this->algorithmInstance;

    deleteChildren();
    delete drawGraph;
    delete dockTop;
    delete dockRight;
    this->close();

    // Showing the MainWindow
    QWidget *parent = this->parentWidget();
    parent->show();
}

void GraphWindow::enableRightDockWindow()
{
    dockRight->setDisabled(false);
}

void GraphWindow::animateRightDockWindow()
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

void GraphWindow::createDockWindows()
{
    createTopDockWindow();
    createRightDockWindow();
}

void GraphWindow::createTopDockWindow()
{
    dockTop = new QDockWidget(this);
    dockTop->setTitleBarWidget(new QWidget());

    pushButtonReturn = new QPushButton(" ", this);
    pushButtonReturn->setFixedWidth(buttonWidth);
    pushButtonReturn->setFixedHeight(buttonHeight);
    pushButtonReturn->setStyleSheet(QString("background-color: #5599ff"));

    connect(pushButtonReturn, &QPushButton::clicked, this, &GraphWindow::pushButtonReturn_clicked);
    dockTop->setWidget(pushButtonReturn);
    addDockWidget(Qt::TopDockWidgetArea, dockTop);
}

void GraphWindow::createRightDockWindow()
{
    dockRight = new QDockWidget(this);
    dockRight->setAttribute(Qt::WA_DeleteOnClose);
    dockRight->setTitleBarWidget(new QWidget()); // remove title bar
    dockRight->setDisabled(true);
    setAlgoGraphAtRightDockWindow();
}

void GraphWindow::changeRightDockWindow()
{
    if(isChild("algoGraph"))
    {
        name = algoGraph->getAlgoName();

        algorithmInstance = algoGraph->getAlgorithmInstance();
        algorithmInstance->setGraph(*currentGraph);
        executeAlgorithm(algorithmInstance);

        deleteChildren();
        setCodeGraphAtRightDockWindow();
    }
    else if(isChild("codeGraph"))
    {
        playback.first = stop;
        GraphAlgorithmDrawingThread::threadAlive.lock();
        playback.first = play;
        GraphAlgorithmDrawingThread::threadAlive.unlock();

        delete algorithmInstance;
        deleteChildren();
        setAlgoGraphAtRightDockWindow();
    }
}

void GraphWindow::setAlgoGraphAtRightDockWindow()
{
    disableThings();
    algoGraph = new AlgoGraph(dockRight);
//    algoGraph->setMinimumWidth(this->width() * 0.2);
    algoGraph->setObjectName("algoGraph");
    algoGraph->getAlgoName();
    dockRight->setWidget(algoGraph);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);
}

void GraphWindow::setCodeGraphAtRightDockWindow()
{
    enableThings();
    codeGraph = new CodeGraph(dockRight);
//    codeGraph->setMinimumWidth(this->width() * 0.35);
    codeGraph->setObjectName("codeGraph");
    dockRight->setWidget(codeGraph);
    addDockWidget(Qt::RightDockWidgetArea, dockRight);

    codeGraph->setText(name, algorithmInstance->getPseudoCodeHTML());
}

void GraphWindow::enableThings()
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

void GraphWindow::disableThings()
{
    minus->setDisabled(true);
    plus->setDisabled(true);
    slider->setDisabled(true);
    ui->actionPlay->setDisabled(true);
    ui->actionPause->setDisabled(true);
    ui->actionStop->setDisabled(true);
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

void GraphWindow::animationSetup()
{
    group = new QSequentialAnimationGroup();

    hideAlgo = new QPropertyAnimation(dockRight, "maximumWidth");
    hideAlgo->setObjectName("hideAlgo");
    hideAlgo->setDuration(700);
    hideAlgo->setStartValue(algoGraph->width());
    hideAlgo->setEndValue(0);

    showCode = new QPropertyAnimation(dockRight, "maximumWidth");
    showCode->setObjectName("showCode");
    showCode->setDuration(500);
    showCode->setStartValue(0);
    showCode->setEndValue(algoGraph->width());

    group->addAnimation(hideAlgo);
    group->addAnimation(showCode);

    group2 = new QSequentialAnimationGroup();

    hideCode = new QPropertyAnimation(dockRight, "maximumWidth");
    hideCode->setObjectName("hideCode");
    hideCode->setDuration(500);
    hideCode->setStartValue(algoGraph->width());
    hideCode->setEndValue(0);

    showAlgo = new QPropertyAnimation(dockRight, "maximumWidth");
    showAlgo->setObjectName("showAlgo");
    showAlgo->setDuration(700);
    showAlgo->setStartValue(0);
    showAlgo->setEndValue(algoGraph->width());

    group2->addAnimation(hideCode);
    group2->addAnimation(showAlgo);
}

void GraphWindow::toolBarSetup()
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
    connect(plus, &QPushButton::clicked, this, &GraphWindow::plus_clicked);
    minus = new QPushButton("-", this);
    connect(minus, &QPushButton::clicked, this, &GraphWindow::minus_clicked);

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

void GraphWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && event->screenPos() == QPoint(-1, -1))
    {
        animateRightDockWindow();
    }
}

void GraphWindow::paintEvent(QPaintEvent *event)
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

void GraphWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if(isChild("codeGraph"))
    {
        dockRight->resize(this->width() * 0.35, dockRight->height());
        codeGraph->setMinimumWidth(this->width() * 0.35);
    }
    else
    {
        dockRight->resize(this->width() * 0.2, dockRight->height());
        algoGraph->setMinimumWidth(this->width() * 0.2);
    }
}

void GraphWindow::setGraph(Graph* g)
{
    this->currentGraph = g;
}

Graph* GraphWindow::getGraph()
{
    return currentGraph;
}

void GraphWindow::executeAlgorithm(GraphAlgorithm* algorithmInstance)
{
    auto thread = new AlgorithmExecutorThread(algorithmInstance);
    QObject::connect(thread, SIGNAL(algorithmExecutionFinished(Algorithm*)),
                     this, SLOT(startAlgorithmPlayback(Algorithm*)));

    QObject::connect(thread, &AlgorithmExecutorThread::algorithmExecutionFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    thread->start();
}

void GraphWindow::clearStylesheets()
{
    this->setStyleSheet(QString());
    ui->toolBar->setStyleSheet(QString());
    Ui::AlgoGraph *uiAlgo = algoGraph->getUi();
    algoGraph->setStyleSheet(QString());
    uiAlgo->pushButtonPrim->setStyleSheet(QString());
    uiAlgo->pushButtonAStar->setStyleSheet(QString());
    uiAlgo->pushButtonBFS->setStyleSheet(QString());
    uiAlgo->pushButtonDFS->setStyleSheet(QString());
    uiAlgo->pushButtonDijkstra->setStyleSheet(QString());
    uiAlgo->pushButtonFW->setStyleSheet(QString());
    pushButtonReturn->setStyleSheet(QString());
    Ui::drawGraph *uiDraw = drawGraph->getUi();
    uiDraw->graphicsView->setStyleSheet(QString());
}

void GraphWindow::setTheme(QFile *file)
{
    clearStylesheets();
    file->open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(file);
    this->setStyleSheet(stream.readAll());
    file->close();
}

void GraphWindow::startAlgorithmPlayback(Algorithm* algo)
{
    GraphAlgorithm* algorithm = dynamic_cast<GraphAlgorithm*>(algo);
    auto thread = new GraphAlgorithmDrawingThread(algorithm);
    QObject::connect(thread, SIGNAL(updateHTML(QString)),
                     this->codeGraph, SLOT(updateHTML(QString)));

    QObject::connect(thread, &GraphAlgorithmDrawingThread::graphAlgorithmDrawingFinished,
                     this, &GraphWindow::playbackFinished,
                     Qt::QueuedConnection);

    QObject::connect(thread, &GraphAlgorithmDrawingThread::graphAlgorithmDrawingFinished,
                     thread, &QObject::deleteLater,
                     Qt::QueuedConnection);

    QObject::connect(thread, &GraphAlgorithmDrawingThread::updateLineInBox,
                     drawGraph, &DrawGraph::updateBox);

    thread->start();
    //TODO delete algorithm on return to main menu
}

void GraphWindow::playbackFinished(bool killed)
{
    if(!killed)
        playback.first = pausE;
    else
        playback.first = play;
}

void GraphWindow::on_actionPlay_triggered()
{
    if(playback.first == pausE && isChild("codeGraph")){
        playback.first = play;
        startAlgorithmPlayback(algorithmInstance);
    }
    playbackMutex.try_lock();
    playback.first = play;
    playbackMutex.unlock();
}

void GraphWindow::on_actionPause_triggered()
{
    playbackMutex.try_lock();
}

void GraphWindow::on_actionStop_triggered()
{
    playbackMutex.try_lock();
    playback.first = stop;
    playbackMutex.unlock();

    GraphAlgorithmDrawingThread::threadAlive.lock();
    GraphAlgorithmDrawingThread::threadAlive.unlock();
    playback.first = play;

    if(isChild("codeGraph"))
        codeGraph->setText(name, algorithmInstance->getPseudoCodeHTML());
}

void GraphWindow::changePlaybackSpeed(int sliderValue)
{
    sliderValue -= slider->maximum() / 2 +1;
    sliderValue = 1000 * pow(2, -sliderValue);
    playback.second = sliderValue;
}

void GraphWindow::on_actionSave_As_Image_triggered()
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

    QGraphicsProxyWidget* doneItem = drawGraph->doneItem;
    QGraphicsProxyWidget* helpItem = drawGraph->helpItem;
    QGraphicsProxyWidget* clearItem = drawGraph->clearItem;
    QGraphicsTextItem* directions = drawGraph->directions;
    Ui::drawGraph* ui = drawGraph->getUi();

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

    drawGraph->grab().save(&file);

    doneItem->setVisible(true);
    helpItem->setVisible(true);
    clearItem->setVisible(true);

    if (returnDirections)
        directions->setVisible(true);

    ui->graphicsView->horizontalScrollBar()->show();
    ui->graphicsView->verticalScrollBar()->show();
}

void GraphWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void GraphWindow::on_actionDiffnes_triggered()
{
    QFile file(":/stylesheets/Diffnes.qss");
    setTheme(&file);
}

void GraphWindow::on_actionCombinear_triggered()
{
    QFile file(":/stylesheets/Combinear.qss");
    setTheme(&file);
}

void GraphWindow::on_actionDarkeum_triggered()
{
    QFile file(":/stylesheets/Darkeum.qss");
    setTheme(&file);
}

void GraphWindow::on_actionIntegrid_triggered()
{
    QFile file(":/stylesheets/Integrid.qss");
    setTheme(&file);
}

void GraphWindow::on_actionMedize_triggered()
{
    QFile file(":/stylesheets/Medize.qss");
    setTheme(&file);
}

void GraphWindow::plus_clicked()
{
    Ui::CodeGraph *ui = codeGraph->getUi();
    qreal z = ui->algoPseudocode->zoomFactor();
    if(z <= 1.7)
        ui->algoPseudocode->setZoomFactor(z + 0.1);
}

void GraphWindow::minus_clicked()
{
    Ui::CodeGraph *ui = codeGraph->getUi();
    qreal z = ui->algoPseudocode->zoomFactor();
    if(z >= 1.1)
        ui->algoPseudocode->setZoomFactor(z - 0.1);
}
