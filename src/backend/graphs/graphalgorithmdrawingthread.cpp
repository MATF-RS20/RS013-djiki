#include "graphalgorithmdrawingthread.hpp"
#include <QDebug>
#include "../../gui/graph/graphwindow.hpp"

GraphAlgorithmDrawingThread::GraphAlgorithmDrawingThread(GraphAlgorithm* algorithmInstance)
    : algorithm(algorithmInstance)
{}

void GraphAlgorithmDrawingThread::run()
{
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
    static Node* activeNode = nullptr;
    static Edge* activeEdge = nullptr;

    if(activeNode)
    {
        activeNode->stopAnimation();
        activeNode = nullptr;
    }

    if(currentState.currentNode)
    {
        activeNode = currentState.currentNode;
        activeNode->animateNode();
    }

    if(currentState.currentEdge)
    {
        activeEdge = currentState.currentEdge;
        activeEdge->animateEdge();
    }

}

void GraphAlgorithmDrawingThread::highlightCurrentPseudocodeLine(unsigned line)
{
    emit updateHTML(algorithm->getPseudoCodeHTML(line));

    QString activeLine = algorithm->getCode().getCode()[static_cast<int>(line)-1];
    emit updateLineInBox(activeLine);
}
