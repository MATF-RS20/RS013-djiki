#ifndef GRAPHALGORITHM_HPP
#define GRAPHALGORITHM_HPP
#include "graphstate.hpp"
#include "../../drawing/graph/graph.hpp"
#include "../pseudocode.hpp"
#include "../algorithm.hpp"

class GraphAlgorithm : public Algorithm
{
public:
    GraphAlgorithm();
    GraphAlgorithm(Graph *g);

    void setGraph(Graph g);
    virtual void solve() = 0;
    virtual ~GraphAlgorithm() = default;

    QVector<GraphState> getStates() const;

protected:
    void addState(Node* currentNode, unsigned currentLine);
    void addState(Node* currentNode, Edge* currentEdge, unsigned currentLine);

    Node* start;
    Node* end;
    Graph graph;
    QVector<GraphState> states;
};

#endif // GRAPHALGORITHM_HPP
