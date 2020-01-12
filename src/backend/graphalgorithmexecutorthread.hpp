#ifndef GRAPHALGORITHMEXECUTORTHREAD_HPP
#define GRAPHALGORITHMEXECUTORTHREAD_HPP
#include <QThread>
#include "graphs/graphalgorithm.hpp"

class GraphAlgorithmExecutorThread : public QThread
{
    Q_OBJECT

public:
    GraphAlgorithmExecutorThread(GraphAlgorithm* algorithmInstance);

signals:
    void graphAlgorithmFinished(GraphAlgorithm* algorithmInstance);

protected:
    void run() override;

private:
    GraphAlgorithm* algorithmInstance;
};

#endif // GRAPHALGORITHMEXECUTORTHREAD_HPP
