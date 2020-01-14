#include "graphalgorithmdrawingthread.hpp"
#include <QDebug>
#include "../../gui/graph/graphwindow.hpp"

QMutex GraphAlgorithmDrawingThread::threadAlive;

GraphAlgorithmDrawingThread::GraphAlgorithmDrawingThread(GraphAlgorithm* algorithmInstance)
    : algorithm(algorithmInstance)
{}

void GraphAlgorithmDrawingThread::run()
{
    bool killed = false;

    QVector<GraphState> states = algorithm->getStates();

    for(auto currentState : states){ 
        threadAlive.tryLock();

        GraphWindow::playbackMutex.lock();
        if(GraphWindow::playback.first == stop)
        {
            killed = true;
            break;
        }
        GraphWindow::playbackMutex.unlock();

        animateCurrentState(currentState);
        highlightCurrentPseudocodeLine(currentState.currentLine);


        unsigned delay = GraphWindow::playback.second;
        QThread::msleep(delay);
    }

    cleanUp();
    emit graphAlgorithmDrawingFinished(killed);
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

void GraphAlgorithmDrawingThread::cleanUp()
{
    QString cleanString = "";
    emit updateLineInBox(cleanString);

    animateCurrentState(GraphState(nullptr, nullptr, 0));
    threadAlive.unlock();
}
