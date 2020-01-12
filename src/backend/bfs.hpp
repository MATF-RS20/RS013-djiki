#ifndef BFS_HPP
#define BFS_HPP
#include "../drawing/graph/graph.hpp"
#include "graphalgorithm.hpp"

class BFS : public GraphAlgorithm
{
public:
    BFS();
    BFS(Graph *g);

    void definePseudocode();
    void solve();
};

#endif // BFS_HPP
