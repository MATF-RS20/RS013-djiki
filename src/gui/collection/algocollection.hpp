#ifndef ALGOCOLLECTION_HPP
#define ALGOCOLLECTION_HPP

#include <QWidget>
#include "../../backend/collections/collectionalgorithm.hpp"

namespace Ui {
class AlgoCollection;
}

class AlgoCollection : public QWidget
{
    Q_OBJECT

public:
    explicit AlgoCollection(QWidget *parent = 0);
    ~AlgoCollection();
    QString getAlgoName();
    CollectionAlgorithm* getAlgorithmInstance();
    Ui::AlgoCollection* getUi() const;

private slots:
    void on_pushButtonBubbleSort_clicked();
    void on_pushButtonInsertionSort_clicked();
    void on_pushButtonQuickSort_clicked();
    void on_pushButtonSelectionSort_clicked();

private:
    Ui::AlgoCollection *ui;
    QString algoName;
    CollectionAlgorithm* algorithmInstance;

    void notifyParent();
};

#endif // ALGOCOLLECTION_HPP
