#include "catch.hpp"
#include "testing.hpp"

#include <QApplication>
#include <QMouseEvent>

#include "../src/drawing/graph/drawgraph.hpp"
#include "../src/drawing/graph/node.hpp"
#include "../src/drawing/graph/edge.hpp"
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

    event.setLocalPos(QPointF(300, 300));
    drawG.mousePressEvent(&event);

    REQUIRE(drawG.getNodes().size() == 3);

    QVector<Node*> nodes = drawG.getNodes();
    QGraphicsSceneMouseEvent* mouseEvent = new QGraphicsSceneMouseEvent();

    SECTION("Nodes without edges deletion")
    {
        mouseEvent->setButton(Qt::RightButton);
        nodes[2]->mousePressEvent(mouseEvent);

        CHECK(drawG.getNodes().size() == 2);
    }

    SECTION("Adding edges")
    {
        REQUIRE(drawG.getEdges().size() == 0);

        mouseEvent->setButton(Qt::LeftButton);
        mouseEvent->setModifiers(Qt::ControlModifier);
        nodes[0]->mousePressEvent(mouseEvent);
        nodes[1]->mousePressEvent(mouseEvent);
    }

    SECTION("On clear graph")
    {
        drawG.onClearGraph();

        REQUIRE(drawG.getNodes().size() == 0);
        REQUIRE(drawG.getEdges().size() == 0);
    }
}


#endif
