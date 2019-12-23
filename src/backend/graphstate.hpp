#ifndef GRAPHSTATE_H
#define GRAPHSTATE_H

#include "../graph/node.hpp"
#include "../graph/edge.hpp"


struct GraphState {
    GraphState() {}
    GraphState(Node* currentNode, Edge* currentEdge, unsigned currentLine)
        : currentNode(currentNode)
        , currentEdge(currentEdge)
        , currentLine(currentLine)
    {}

    Node* currentNode;
    Edge* currentEdge;
    unsigned currentLine;
};



#endif // GRAPHSTATE_H
