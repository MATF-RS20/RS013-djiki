#include "graphalgorithmdrawingthread.hpp"
#include <QDebug>

GraphAlgorithmDrawingThread::GraphAlgorithmDrawingThread(QVector<GraphState> states)
    : states(states)
{}

void GraphAlgorithmDrawingThread::run()
{
    //TODO check mutex for play/pause/speed change in every iteration
    unsigned delay = 1;
    for(auto currentState : states){
        qDebug() << currentState.currentLine;
        animateCurrentState(currentState);
        highlightCurrentPseudocodeLine(currentState.currentLine);
        sleep(delay);
    }

    emit graphAlgorithmDrawingFinished();
}

void GraphAlgorithmDrawingThread::animateCurrentState(GraphState currentState)
{
    //TODO
}

void GraphAlgorithmDrawingThread::highlightCurrentPseudocodeLine(unsigned line)
{
    //TODO
}
