#include "graphalgorithmexecutorthread.hpp"

GraphAlgorithmExecutorThread::GraphAlgorithmExecutorThread(BFS* algorithmInstance)
    :algorithmInstance(algorithmInstance)
{

}

void GraphAlgorithmExecutorThread::run()
{
    algorithmInstance->solve();
    emit graphAlgorithmFinished(algorithmInstance);
}
