#include "graphalgorithmdrawingthread.hpp"
#include <QDebug>

GraphAlgorithmDrawingThread::GraphAlgorithmDrawingThread(GraphAlgorithm* algorithmInstance)
    : algorithm(algorithmInstance)
{}

void GraphAlgorithmDrawingThread::run()
{
    //TODO check mutex for play/pause/speed change in every iteration
    unsigned delay = 1;
    QVector<GraphState> states = algorithm->getStates();
    for(auto currentState : states){ 
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
    emit updateHTML(algorithm->getPseudoCodeHTML(line));
}
