#ifndef COLLECTIONALGORITHMDRAWINGTHREAD_HPP
#define COLLECTIONALGORITHMDRAWINGTHREAD_HPP

#include <QThread>
#include "collectionstate.hpp"
#include "collectionalgorithm.hpp"

class CollectionAlgorithmDrawingThread : public QThread
{
    Q_OBJECT

public:
    CollectionAlgorithmDrawingThread(CollectionAlgorithm* algorithmInstance, Collection collection);

signals:
    void collectionAlgorithmDrawingFinished();
    void updateHTML(QString html);
    void updateLineInBox(QString line);

protected:
    void run() override;

private:
    void animateCurrentState(CollectionState currentState);
    void highlightCurrentPseudocodeLine(unsigned line);
    CollectionAlgorithm* algorithm;
    Collection collection;
};


#endif // COLLECTIONALGORITHMDRAWINGTHREAD_HPP
