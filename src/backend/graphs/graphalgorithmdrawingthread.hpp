#ifndef GRAPHALGORITHMDRAWINGTHREAD_HPP
#define GRAPHALGORITHMDRAWINGTHREAD_HPP

#include <QThread>
#include "graphstate.hpp"
#include "graphalgorithm.hpp"

class GraphAlgorithmDrawingThread : public QThread
{
    Q_OBJECT

public:
    GraphAlgorithmDrawingThread(GraphAlgorithm* algorithmInstance);

signals:
    void graphAlgorithmDrawingFinished();
    void updateHTML(QString html);
    void updateLineInBox(QString line);

protected:
    void run() override;

private:
    void animateCurrentState(GraphState currentState);
    void highlightCurrentPseudocodeLine(unsigned line);
    GraphAlgorithm* algorithm;
};


#endif // GRAPHALGORITHMDRAWINGTHREAD_HPP
