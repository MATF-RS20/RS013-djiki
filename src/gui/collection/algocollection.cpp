#include "algocollection.hpp"
#include "ui_algocollection.h"
#include <QMouseEvent>
#include <QtDebug>

#include "../../backend/collections/algorithms/bubblesort.hpp"
#include "../../backend/collections/algorithms/selectionsort.hpp"
#include "../../backend/collections/algorithms/insertionsort.hpp"

AlgoCollection::AlgoCollection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoCollection)
{
    ui->setupUi(this);
}

AlgoCollection::~AlgoCollection()
{
    delete ui;
}

QString AlgoCollection::getAlgoName()
{
    return AlgoCollection::algoName;
}

CollectionAlgorithm* AlgoCollection::getAlgorithmInstance()
{
    return AlgoCollection::algorithmInstance;
}

Ui::AlgoCollection *AlgoCollection::getUi() const
{
    return ui;
}

void AlgoCollection::notifyParent()
{
    QPoint pos(this->width()/2, this->height()/2);
    QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, pos, QPoint(-1, -1), Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);
    QCoreApplication::postEvent(this->parent(), event);
}

void AlgoCollection::on_pushButtonBubbleSort_clicked()
{
    algoName = "Bubble Sort";
    algorithmInstance = new BubbleSort();

    notifyParent();
}

void AlgoCollection::on_pushButtonInsertionSort_clicked()
{
    algoName = "Insertion Sort";
    algorithmInstance = new InsertionSort();

    notifyParent();
}

void AlgoCollection::on_pushButtonMergeSort_clicked()
{
    algoName = "Merge Sort";

    notifyParent();
}

void AlgoCollection::on_pushButtonQuickSort_clicked()
{
    algoName = "Quick Sort";

    notifyParent();
}

void AlgoCollection::on_pushButtonSelectionSort_clicked()
{
    algoName = "Selection Sort";
    algorithmInstance = new SelectionSort();

    notifyParent();
}

void AlgoCollection::on_pushButtonBinarySearch_clicked()
{
    algoName = "Binary Search";

    notifyParent();
}
