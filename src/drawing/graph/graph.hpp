#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include "node.hpp"
#include "edge.hpp"
#include <QVector>
#include <QMap>

class Graph
{
public:
    Graph();
    Graph(QVector<Node*> *nodes, QVector<Edge*> *edges);

    Node* getNodeByNodeNumber(unsigned n) const;
    Edge* getEdgeFromTo(const Node* start, const Node* end) const;

    const QVector<Node*> getNeighbours(Node* node) const;
    const QMap<Node*, int> getNeighboursWeighted(Node* node) const;
    const QVector<Node*> getNodes() const;

    unsigned getGraphSize();
private:
    QVector<Node*> *nodes;
    QVector<Edge*> *edges;
};

#endif // GRAPH_HPP
