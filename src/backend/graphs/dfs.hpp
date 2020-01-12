#ifndef DFS_HPP
#define DFS_HPP
#include "../../drawing/graph/graph.hpp"
#include "graphalgorithm.hpp"

class DFS : public GraphAlgorithm
{
public:
    DFS();
    DFS(Graph *g);

    void definePseudocode();
    void solve();
};

#endif // DFS_HPP
