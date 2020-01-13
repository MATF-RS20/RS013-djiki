#include "graph.hpp"
#include <algorithm>

Graph::Graph()
{}

Graph::Graph(QVector<Node*> *nodes, QVector<Edge*> *edges)
: nodes(nodes)
, edges(edges)
{}

Node* Graph::getNodeByNodeNumber(unsigned n) const
{
    for(auto node : *this->nodes)
    {
        if(node->getNodeNumber() == n)
            return node;
    }

    return nullptr;
}

Edge* Graph::getEdgeFromTo(const Node* start, const Node* end) const
{
    for(auto edge : *this->edges)
    {
        if(edge->getStart() == start && edge->getEnd() == end)
            return edge;
    }

    return nullptr;
}

const QVector<Node*> Graph::getNodes() const
{
    return *nodes;
}

const QVector<Node*> Graph::getNeighbours(Node* node) const
{
    return node->getNeighbours();
}

const QMap<Node*, int> Graph::getNeighboursWeighted(Node* node) const
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
