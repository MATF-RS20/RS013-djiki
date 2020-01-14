#ifndef COLLECTIONALGORITHMDRAWINGTHREAD_HPP
#define COLLECTIONALGORITHMDRAWINGTHREAD_HPP

#include <QThread>
#include "collectionstate.hpp"
#include "collectionalgorithm.hpp"
#include <QMutex>

class CollectionAlgorithmDrawingThread : public QThread
{
    Q_OBJECT

public:
    CollectionAlgorithmDrawingThread(CollectionAlgorithm* algorithmInstance, Collection collection);
    static QMutex threadAlive;

signals:
    void collectionAlgorithmDrawingFinished(bool killed);
    void updateHTML(QString html);
    void updateLineInBox(QString line);

protected:
    void run() override;

private:
    void animateCurrentState(CollectionState currentState);
    void highlightCurrentPseudocodeLine(unsigned line);
    void cleanUp();

    CollectionAlgorithm* algorithm;
    Collection collection;
    QVector<int> snapshot;
};


#endif // COLLECTIONALGORITHMDRAWINGTHREAD_HPP
