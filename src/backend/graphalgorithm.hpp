#ifndef GRAPHALGORITHM_HPP
#define GRAPHALGORITHM_HPP
#include "graphstate.hpp"
#include "../drawing/graph/graph.hpp"
#include "pseudocode.hpp"

class GraphAlgorithm
{
public:
    GraphAlgorithm();
    GraphAlgorithm(Graph *g);

    void setGraph(Graph g);
    virtual void solve() = 0;

    QString getOutcome() const;
    QVector<GraphState> getStates() const;
    QString getPseudoCodeHTML(unsigned activeLine = 0) const;
protected:
    void addState(Node* currentNode, unsigned currentLine);
    void addState(Node* currentNode, Edge* currentEdge, unsigned currentLine);

    Node* start;
    Node* end;
    Graph graph;
    QVector<GraphState> states;
    QString outcome;
    Pseudocode code;
};

#endif // GRAPHALGORITHM_HPP
