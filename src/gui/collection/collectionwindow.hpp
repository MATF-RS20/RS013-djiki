#ifndef COLLECTIONWINDOW_HPP
#define COLLECTIONWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class CollectionWindow;
}

class CollectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollectionWindow(QWidget *parent = 0);
    ~CollectionWindow();

private slots:
    void pushButtonReturn_clicked();

private:
    void createDockWindows();
    QPushButton *pushButtonReturn;

    Ui::CollectionWindow *ui;
};

#endif // COLLECTIONWINDOW_HPP
