#ifndef COLLECTIONWINDOW_HPP
#define COLLECTIONWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class CollectionWindow;
}

class CollectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollectionWindow(QWidget *parent = 0);
    ~CollectionWindow();

private:
    Ui::CollectionWindow *ui;
};

#endif // COLLECTIONWINDOW_HPP
