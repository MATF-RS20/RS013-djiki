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
    Graph(QVector<Node*> *nodes, QVector<Edge*> *edges);

    Node* getNodeByNodeNumber(unsigned n) const;
    const QVector<Node*> getNeighbours(Node* node) const;
    const QMap<Node*, int> getNeighboursWeighted(Node* node) const;
    unsigned getGraphSize();
private:
    QVector<Node*> *nodes;
    QVector<Edge*> *edges;
};

#endif // GRAPH_HPP
