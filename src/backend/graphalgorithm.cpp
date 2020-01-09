#include "graphalgorithm.hpp"

GraphAlgorithm::GraphAlgorithm(Graph *g)
    : graph(*g)
{
    start = graph.getNodeByNodeNumber(0);
    end = graph.getNodeByNodeNumber(graph.getGraphSize()-1);
}


QString GraphAlgorithm::getOutcome() const
{
    return outcome;
}


QVector<GraphState> GraphAlgorithm::getStates() const
{
    return states;
}

void GraphAlgorithm::addState(Node* currentNode, unsigned currentLine)
{
    this->states.append(GraphState(currentNode, nullptr, currentLine));
}

void GraphAlgorithm::addState(Node* currentNode, Edge* currentEdge, unsigned currentLine)
{
    this->states.append(GraphState(currentNode, currentEdge, currentLine));
}

QString GraphAlgorithm::getPseudoCodeHTML(unsigned activeLine) const
{
    return code.generateHTML(activeLine);
}
