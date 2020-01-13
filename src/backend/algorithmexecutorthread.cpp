#include "algorithmexecutorthread.hpp"

AlgorithmExecutorThread::AlgorithmExecutorThread(Algorithm* algorithmInstance)
    :algorithmInstance(algorithmInstance)
{

}

void AlgorithmExecutorThread::run()
{
    algorithmInstance->solve();
    emit algorithmExecutionFinished(algorithmInstance);
}
