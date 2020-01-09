QT       += core gui

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
    src/backend/bfs.cpp \
    src/backend/graphalgorithm.cpp \
    src/backend/graphalgorithmdrawingthread.cpp \
    src/backend/graphalgorithmexecutorthread.cpp \
    src/graph/drawgraph.cpp \
    src/graph/edge.cpp \
    src/graph/graph.cpp \
    src/graph/node.cpp \
    src/gui/collectionwindow.cpp \
    src/gui/graphwindow.cpp \
    src/gui/main.cpp \
    src/gui/mainwindow.cpp \
    src/gui/algograph.cpp \
    src/gui/codegraph.cpp \
    src/gui/graphcodeedit.cpp \
    src/gui/graphcodelinenumber.cpp

HEADERS += \
    src/backend/bfs.hpp \
    src/backend/graphalgorithm.hpp \
    src/backend/graphalgorithmdrawingthread.hpp \
    src/backend/graphalgorithmexecutorthread.hpp \
    src/backend/graphstate.hpp \
    src/backend/pseudocode.hpp \
    src/graph/drawgraph.hpp \
    src/graph/edge.hpp \
    src/graph/graph.hpp \
    src/graph/node.hpp \
    src/gui/collectionwindow.hpp \
    src/gui/graphwindow.hpp \
    src/gui/mainwindow.hpp \
    src/gui/algograph.hpp \
    src/gui/codegraph.hpp \
    src/gui/graphcodeedit.hpp \
    src/gui/graphcodelinenumber.hpp

FORMS += \
    src/graph/drawgraph.ui \
    src/gui/collectionwindow.ui \
    src/gui/graphwindow.ui \
    src/gui/mainwindow.ui \
    src/gui/algograph.ui \
    src/gui/codegraph.ui \
    src/gui/graphcodeedit.ui \
    src/gui/graphcodelinenumber.ui

RESOURCES += \
    src/gui/images/images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
