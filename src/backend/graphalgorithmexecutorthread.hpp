#ifndef GRAPHALGORITHMEXECUTORTHREAD_HPP
#define GRAPHALGORITHMEXECUTORTHREAD_HPP
#include <QThread>
#include "bfs.hpp"

class GraphAlgorithmExecutorThread : public QThread
{
    Q_OBJECT

public:
    GraphAlgorithmExecutorThread(BFS* algorithmInstance);

signals:
    void graphAlgorithmFinished(BFS* algorithmInstance);

protected:
    void run() override;

private:
    BFS* algorithmInstance;
};

#endif // GRAPHALGORITHMEXECUTORTHREAD_HPP
