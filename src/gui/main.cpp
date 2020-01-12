#include "mainwindow.hpp"
#include "../../tests/testing.hpp"
#include "../drawing/collections/drawcollection.hpp"

#include <QApplication>

/* If you want to run tests go to testing.hpp and define UNIT_TESTS_ENABLED macro*/

#ifdef UNIT_TESTS_ENABLED

#define CATCH_CONFIG_MAIN
#include "../../tests/catch.hpp"

#else

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

#endif
