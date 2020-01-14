#include "collectionalgorithmdrawingthread.hpp"
#include <QDebug>
#include "../../gui/collection/collectionwindow.hpp"

QMutex CollectionAlgorithmDrawingThread::threadAlive;

CollectionAlgorithmDrawingThread::CollectionAlgorithmDrawingThread(CollectionAlgorithm* algorithmInstance, Collection collection)
    : algorithm(algorithmInstance)
    , collection(collection)
{
    int i = 0;
    for(auto item : collection.getItems())
    {
        snapshot.push_back(item->getItemValue());
        i++;
    }
}

void CollectionAlgorithmDrawingThread::run()
{
    bool killed = false;

    QVector<CollectionState> states = algorithm->getStates();

    for(auto currentState : states){
        threadAlive.tryLock();

        CollectionWindow::playbackMutex.lock();
        if(CollectionWindow::playback.first == stop)
        {
            killed = true;
            break;
        }
        CollectionWindow::playbackMutex.unlock();

        animateCurrentState(currentState);
        highlightCurrentPseudocodeLine(currentState.currentLine);


        unsigned delay = CollectionWindow::playback.second;
        QThread::msleep(delay);
    }

    cleanUp();
    emit collectionAlgorithmDrawingFinished(killed);
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

void CollectionAlgorithmDrawingThread::cleanUp()
{
    QString cleanString = "";
    emit updateLineInBox(cleanString);

    animateCurrentState(CollectionState(nullptr, nullptr, snapshot, 0));
    threadAlive.unlock();
}
