#ifndef GRAPHALGORITHMEXECUTORTHREAD_HPP
#define GRAPHALGORITHMEXECUTORTHREAD_HPP
#include <QThread>
#include "graphs/graphalgorithm.hpp"

class AlgorithmExecutorThread : public QThread
{
    Q_OBJECT

public:
    AlgorithmExecutorThread(Algorithm* algorithmInstance);

signals:
    void algorithmExecutionFinished(Algorithm* algorithmInstance);

protected:
    void run() override;

private:
    Algorithm* algorithmInstance;
};

#endif // GRAPHALGORITHMEXECUTORTHREAD_HPP
