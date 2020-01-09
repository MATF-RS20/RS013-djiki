#ifndef BFS_HPP
#define BFS_HPP
#include "../graph/graph.hpp"
#include "graphalgorithm.hpp"

class BFS : public GraphAlgorithm
{
public:
    BFS(Graph *g);

    void solve();
};

#endif // BFS_HPP
