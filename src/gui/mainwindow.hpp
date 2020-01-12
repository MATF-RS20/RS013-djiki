#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "graph/graphwindow.hpp"
#include "collection/collectionwindow.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonGraph_clicked();
    void on_pushButtonCollection_clicked();

private:
    Ui::MainWindow *ui;
    GraphWindow *graphWindow;
    CollectionWindow *collectionWindow;
};
#endif // MAINWINDOW_HPP
