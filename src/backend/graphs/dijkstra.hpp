#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include "../../drawing/graph/graph.hpp"
#include "graphalgorithm.hpp"

class Dijkstra : public GraphAlgorithm
{
public:
    Dijkstra();
    Dijkstra(Graph *g);

    void definePseudocode();
    void solve();
};

#endif // DIJKSTRA_HPP
