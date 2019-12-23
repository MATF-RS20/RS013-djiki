#include "graph.hpp"
#include <algorithm>

Graph::Graph(QVector<Node*> *nodes, QVector<Edge*> *edges)
: nodes(nodes)
, edges(edges)
{}

const Node* Graph::getNodeByNodeNumber(unsigned n) const
{
    for(auto node : *this->nodes)
    {
        if(node->getNodeNumber() == n)
            return node;
    }

    return nullptr;
}

const QVector<Node*> Graph::getNeighbours(const Node* node) const
{
    return node->getNeighbours();
}

const QMap<Node*, int> Graph::getNeighboursWeighted(const Node* node) const
{
    QMap<Node*, int> neighbours;
    for(auto edge : *this->edges)
    {
        if(edge->getStart() == node)
            neighbours[edge->getEnd()] = edge->getEdgeWeight();
    }
    return neighbours;
}

unsigned Graph::getGraphSize()
{
    return static_cast<unsigned>(this->nodes->size());
}
