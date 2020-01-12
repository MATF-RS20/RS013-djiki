#ifndef COLLECTIONWINDOW_HPP
#define COLLECTIONWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include "../../drawing/collections/drawcollection.hpp"
#include "algocollection.hpp"
#include "codecollection.hpp"

namespace Ui {
class CollectionWindow;
}

class CollectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollectionWindow(QWidget *parent = 0);
    ~CollectionWindow();
    const static int triangleWidth = 50;
    const static int buttonWidth = 150;
    const static int buttonHeight = 40;

private slots:
    void pushButtonReturn_clicked();

private:
    void createDockWindows();
    void createTopDockWindow();
    void createRightDockWindow();
    void setAlgoCollectionAtRightDockWindow();
    void setCodeCollectionAtRightDockWindow();
    bool isChild(const QString &str);
    void deleteChildren();

    Ui::CollectionWindow *ui;
    DrawCollection *drawCollection;
    AlgoCollection *algoCollection;
    CodeCollection *codeCollection;

    QDockWidget *dockRight;
    QDockWidget *dockTop;
    QPushButton *pushButtonReturn;
};

#endif // COLLECTIONWINDOW_HPP
