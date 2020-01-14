#ifndef GRAPHALGORITHMDRAWINGTHREAD_HPP
#define GRAPHALGORITHMDRAWINGTHREAD_HPP

#include <QThread>
#include "graphstate.hpp"
#include "graphalgorithm.hpp"
#include <QMutex>

class GraphAlgorithmDrawingThread : public QThread
{
    Q_OBJECT

public:
    GraphAlgorithmDrawingThread(GraphAlgorithm* algorithmInstance);
    static QMutex threadAlive;

signals:
    void graphAlgorithmDrawingFinished(bool killed);
    void updateHTML(QString html);
    void updateLineInBox(QString line);

protected:
    void run() override;

private:
    void animateCurrentState(GraphState currentState);
    void highlightCurrentPseudocodeLine(unsigned line);
    void cleanUp();

    GraphAlgorithm* algorithm;
};


#endif // GRAPHALGORITHMDRAWINGTHREAD_HPP
