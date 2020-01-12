#include "graphalgorithmdrawingthread.hpp"
#include <QDebug>
#include "../../gui/graphwindow.hpp"

GraphAlgorithmDrawingThread::GraphAlgorithmDrawingThread(GraphAlgorithm* algorithmInstance)
    : algorithm(algorithmInstance)
{}

void GraphAlgorithmDrawingThread::run()
{
    //TODO check mutex for play/pause/speed change in every iteration
    QVector<GraphState> states = algorithm->getStates();
    for(auto currentState : states){ 

        GraphWindow::playbackMutex.lock();
        if(GraphWindow::playback.first == stop)
            break;
        GraphWindow::playbackMutex.unlock();

        animateCurrentState(currentState);
        highlightCurrentPseudocodeLine(currentState.currentLine);


        unsigned delay = GraphWindow::playback.second;
        QThread::msleep(delay);
    }

    emit graphAlgorithmDrawingFinished();
}

void GraphAlgorithmDrawingThread::animateCurrentState(GraphState currentState)
{
    //TODO
}

void GraphAlgorithmDrawingThread::highlightCurrentPseudocodeLine(unsigned line)
{
    emit updateHTML(algorithm->getPseudoCodeHTML(line));
}
