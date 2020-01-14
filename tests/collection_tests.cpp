#include "catch.hpp"
#include "testing.hpp"

#include <QApplication>
#include <QMouseEvent>

#include "../src/drawing/collections/drawcollection.hpp"
#include "../src/drawing/collections/item.hpp"
#include "../src/drawing/collections/connection.hpp"
#include "../src/gui/mainwindow.hpp"

#ifdef UNIT_TESTS_ENABLED

TEST_CASE("Collection drawing")
{
    int argc = 1;
    char* argv = new char[1];
    QApplication a(argc, &argv);

    DrawCollection drawC(nullptr);

    REQUIRE(drawC.getConnections().size() == 0);
    REQUIRE(drawC.getItems().size() == 0);

    QMouseEvent event(QEvent::MouseButtonPress, QPointF(100, 100), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

    drawC.mousePressEvent(&event);
    drawC.mousePressEvent(&event);

    QVector<Item*> items = drawC.getItems();
    REQUIRE(items.size() == 2);
    REQUIRE(drawC.getConnections().size() == 1);

    QGraphicsSceneMouseEvent* mouseEvent = new QGraphicsSceneMouseEvent();

    SECTION("Items deletion - right click on item")
    {
        mouseEvent->setButton(Qt::RightButton);
        items[1]->mousePressEvent(mouseEvent);

        CHECK(drawC.getItems().size() == 1);
    }

    SECTION("When user clicks 'Clear' button items and connections vectors should be empty")
    {
        drawC.onClearCollection();

        REQUIRE(drawC.getItems().size() == 0);
        REQUIRE(drawC.getConnections().size() == 0);
    }

    SECTION("When user clicks 'Done drawing collection', everything on scene should be disabled")
    {
        drawC.onDoneDrawing();

        CHECK(drawC.doneItem->isEnabled() == false);
        CHECK(drawC.clearItem->isEnabled() == false);
        CHECK(drawC.helpItem->isVisible() == false);

        QVector<Item*> items = drawC.getItems();
        for (auto& i: items)
            CHECK(i->isEnabled() == false);

        QVector<Connection*> connections = drawC.getConnections();
        for (auto& c: connections)
            CHECK(c->isEnabled() == false);
    }
}

#endif
