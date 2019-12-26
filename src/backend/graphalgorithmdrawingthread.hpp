#ifndef GRAPHALGORITHMDRAWINGTHREAD_HPP
#define GRAPHALGORITHMDRAWINGTHREAD_HPP

#include <QThread>
#include "graphstate.hpp"

class GraphAlgorithmDrawingThread : public QThread
{
    Q_OBJECT

public:
    GraphAlgorithmDrawingThread(QVector<GraphState> states);

signals:
    void graphAlgorithmDrawingFinished();

protected:
    void run() override;

private:
    void animateCurrentState(GraphState currentState);
    void highlightCurrentPseudocodeLine(unsigned line);
    QVector<GraphState> states;
};


#endif // GRAPHALGORITHMDRAWINGTHREAD_HPP
