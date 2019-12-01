#include "mainwindow.hpp"
#include "drawgraph.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Uncomment to see the drawing graph part
//    w.setHidden(true);
//    DrawGraph g;
//    g.setFocus();
//    g.show();

    return a.exec();
}
