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

    const Node* getNodeByNodeNumber(unsigned n) const;
    const QVector<Node*> getNeighbours(const Node* node) const;
    const QMap<Node*, int> getNeighboursWeighted(const Node* node) const;
    unsigned getGraphSize();
private:
    QVector<Node*> *nodes;
    QVector<Edge*> *edges;
};

#endif // GRAPH_HPP
