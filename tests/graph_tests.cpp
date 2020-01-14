#include "catch.hpp"
#include "testing.hpp"

#include <QApplication>
#include <QMouseEvent>

#include "../src/drawing/graph/drawgraph.hpp"
#include "../src/drawing/graph/node.hpp"
#include "../src/drawing/graph/edge.hpp"
#include "../src/gui/mainwindow.hpp"

#ifdef UNIT_TESTS_ENABLED

TEST_CASE("Graph drawing")
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

    SECTION("Nodes without edges deletion - right click on node")
    {
        mouseEvent->setButton(Qt::RightButton);
        nodes[2]->mousePressEvent(mouseEvent);

        CHECK(drawG.getNodes().size() == 2);
    }

    SECTION("Adding edges by clicking on two nodes")
    {
        REQUIRE(drawG.getEdges().size() == 0);

        /* Test can not be continued due to user input part */
    }

    SECTION("When user clicks 'Clear' button nodes and edges vectors should be empty")
    {
        drawG.onClearGraph();

        REQUIRE(drawG.getNodes().size() == 0);
        REQUIRE(drawG.getEdges().size() == 0);
    }

    SECTION("When user clicks 'Done drawing graph', everything on scene should be disabled")
    {
        drawG.onDoneDrawing();

        CHECK(drawG.doneItem->isEnabled() == false);
        CHECK(drawG.clearItem->isEnabled() == false);
        CHECK(drawG.helpItem->isVisible() == false);

        QVector<Node*> nodes = drawG.getNodes();
        for (auto& n: nodes)
            CHECK(n->isEnabled() == false);

        QVector<Edge*> edges = drawG.getEdges();
        for (auto& e: edges)
            CHECK(e->isEnabled() == false);
    }
}


#endif
