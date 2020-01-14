#include "collectionalgorithmdrawingthread.hpp"
#include <QDebug>
#include "../../gui/collection/collectionwindow.hpp"

CollectionAlgorithmDrawingThread::CollectionAlgorithmDrawingThread(CollectionAlgorithm* algorithmInstance, Collection collection)
    : algorithm(algorithmInstance)
    , collection(collection)
{}

void CollectionAlgorithmDrawingThread::run()
{

    QVector<CollectionState> states = algorithm->getStates();
    for(auto currentState : states){ 

        CollectionWindow::playbackMutex.lock();
        if(CollectionWindow::playback.first == stop)
            break;
        CollectionWindow::playbackMutex.unlock();

        animateCurrentState(currentState);
        highlightCurrentPseudocodeLine(currentState.currentLine);


        unsigned delay = CollectionWindow::playback.second;
        QThread::msleep(delay);
    }

    emit collectionAlgorithmDrawingFinished();
}

void CollectionAlgorithmDrawingThread::animateCurrentState(CollectionState currentState)
{
    static Item* activeItem = nullptr;
    static Item* activeItemSecond = nullptr;

    if(activeItem)
    {
        activeItem->stopAnimation();
        activeItem = nullptr;
    }

    if(activeItemSecond)
    {
        activeItemSecond->stopAnimation();
        activeItemSecond = nullptr;
    }


    if(currentState.currentItem)
    {
        activeItem = currentState.currentItem;
        activeItem->animateItem();
    }

    if(currentState.currentItemSecond)
    {
        activeItemSecond = currentState.currentItemSecond;
        activeItemSecond->animateItem();
    }

    if(!currentState.currentCollcetionSnapshot.empty())
    {
        int i = 0;
        for(auto item : collection.getItems())
        {
            item->setItemValue(currentState.currentCollcetionSnapshot[i]);
            i++;
        }
    }

}

void CollectionAlgorithmDrawingThread::highlightCurrentPseudocodeLine(unsigned line)
{
    emit updateHTML(algorithm->getPseudoCodeHTML(line));

    QString activeLine = algorithm->getCode().getCode()[static_cast<int>(line)-1];
    emit updateLineInBox(activeLine);
}
