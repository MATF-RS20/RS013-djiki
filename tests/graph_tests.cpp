#include "catch.hpp"
#include "testing.hpp"

#include <QApplication>
#include <QMouseEvent>

#include "../src/graph/drawgraph.hpp"
#include "../src/graph/node.hpp"
#include "../src/graph/edge.hpp"
#include "../src/gui/mainwindow.hpp"

#ifdef UNIT_TESTS_ENABLED

TEST_CASE("Adding nodes")
{
    int argc = 1;
    char* argv = new char[1];
    QApplication a(argc, &argv);

    DrawGraph drawG(nullptr);

    REQUIRE(drawG.getNodes().size() == 0);

    QMouseEvent event(QEvent::MouseButtonPress, QPointF(100, 100), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    drawG.mousePressEvent(&event);

    event.setLocalPos(QPointF(200, 200));
    drawG.mousePressEvent(&event);

    REQUIRE(drawG.getNodes().size() == 2);
}

#endif
