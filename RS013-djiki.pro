QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/backend/algorithm.cpp \
    src/backend/algorithmexecutorthread.cpp \
    src/backend/collections/algorithms/bubblesort.cpp \
    src/backend/collections/collectionalgorithm.cpp \
    src/backend/collections/collectionalgorithmdrawingthread.cpp \
    src/backend/graphs/bfs.cpp \
    src/backend/graphs/dfs.cpp \
    src/backend/graphs/dijkstra.cpp \
    src/backend/graphs/graphalgorithm.cpp \
    src/backend/graphs/graphalgorithmdrawingthread.cpp \
    src/backend/pseudocodeformatter.cpp \
    src/drawing/collections/collection.cpp \
    src/drawing/collections/connection.cpp \
    src/drawing/collections/drawcollection.cpp \
    src/drawing/collections/item.cpp \
    src/drawing/drawingFunctions.cpp \
    src/drawing/graph/drawgraph.cpp \
    src/drawing/graph/edge.cpp \
    src/drawing/graph/graph.cpp \
    src/drawing/graph/node.cpp \
    tests/graph_tests.cpp \
    src/gui/collection/collectionwindow.cpp \
    src/gui/graph/algograph.cpp \
    src/gui/graph/codegraph.cpp \
    src/gui/graph/graphcodeedit.cpp \
    src/gui/graph/graphwindow.cpp \
    src/gui/main.cpp \
    src/gui/mainwindow.cpp \
    src/gui/collection/algocollection.cpp \
    src/gui/collection/codecollection.cpp \
    src/gui/collection/collectioncodeedit.cpp

HEADERS += \
    src/backend/algorithm.hpp \
    src/backend/algorithmexecutorthread.hpp \
    src/backend/collections/algorithms/bubblesort.hpp \
    src/backend/collections/collectionalgorithm.hpp \
    src/backend/collections/collectionalgorithmdrawingthread.hpp \
    src/backend/collections/collectionstate.hpp \
    src/backend/graphs/bfs.hpp \
    src/backend/graphs/dfs.hpp \
    src/backend/graphs/dijkstra.hpp \
    src/backend/graphs/graphalgorithm.hpp \
    src/backend/graphs/graphalgorithmdrawingthread.hpp \
    src/backend/graphs/graphstate.hpp \
    src/backend/pseudocode.hpp \
    src/backend/pseudocodeformatter.hpp \
    src/drawing/collections/collection.hpp \
    src/drawing/collections/connection.hpp \
    src/drawing/collections/drawcollection.hpp \
    src/drawing/collections/item.hpp \
    src/drawing/drawingFunctions.hpp \
    src/drawing/graph/drawgraph.hpp \
    src/drawing/graph/edge.hpp \
    src/drawing/graph/graph.hpp \
    src/drawing/graph/node.hpp \
    src/gui/playbacksettings.hpp \
    tests/testing.hpp \
    src/gui/collection/collectionwindow.hpp \
    src/gui/graph/algograph.hpp \
    src/gui/graph/codegraph.hpp \
    src/gui/graph/graphcodeedit.hpp \
    src/gui/graph/graphwindow.hpp \
    src/gui/mainwindow.hpp \
    src/gui/collection/algocollection.hpp \
    src/gui/collection/codecollection.hpp \
    src/gui/collection/collectioncodeedit.hpp

FORMS += \
    src/drawing/collections/drawcollection.ui \
    src/drawing/graph/drawgraph.ui \
    src/gui/collection/collectionwindow.ui \
    src/gui/graph/algograph.ui \
    src/gui/graph/codegraph.ui \
    src/gui/graph/graphcodeedit.ui \
    src/gui/graph/graphwindow.ui \
    src/gui/mainwindow.ui \
    src/gui/collection/algocollection.ui \
    src/gui/collection/codecollection.ui \
    src/gui/collection/collectioncodeedit.ui

RESOURCES += \
    src/gui/images/images.qrc \
    src/gui/stylesheets/stylesheets.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
