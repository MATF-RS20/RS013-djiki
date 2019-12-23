#ifndef BFS_HPP
#define BFS_HPP
#include "graphstate.hpp"
#include "../graph/graph.hpp"

class BFS
{
public:
    BFS(Graph *g);

    void solve();
    QString getOutcome() const;
    QVector<GraphState> getStates() const;

private:
    void addState(Node* currentNode, unsigned currentLine);
    void addState(Node* currentNode, Edge* currentEdge, unsigned currentLine);

    Node* start;
    Node* end;
    Graph graph;
    QVector<GraphState> states;
    QString outcome;
};

#endif // BFS_HPP
