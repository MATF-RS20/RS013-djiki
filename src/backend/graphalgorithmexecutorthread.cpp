#include "graphalgorithmexecutorthread.hpp"

GraphAlgorithmExecutorThread::GraphAlgorithmExecutorThread(GraphAlgorithm* algorithmInstance)
    :algorithmInstance(algorithmInstance)
{

}

void GraphAlgorithmExecutorThread::run()
{
    algorithmInstance->solve();
    emit graphAlgorithmFinished(algorithmInstance);
}
