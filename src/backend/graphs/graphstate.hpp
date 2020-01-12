#ifndef GRAPHSTATE_H
#define GRAPHSTATE_H

#include "../../drawing/graph/node.hpp"
#include "../../drawing/graph/edge.hpp"


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
