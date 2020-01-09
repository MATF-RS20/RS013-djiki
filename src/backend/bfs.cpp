#include "bfs.hpp"
#include <queue>

BFS::BFS(Graph *g)
    : GraphAlgorithm(g)
{}

void BFS::solve()
{
    std::queue<Node*> S;
    S.push(start);
    QMap<Node*, Node*> parent;
    parent[start] = start;
    addState(start, 1);

    while (!S.empty())
    {
        Node* n = S.back();
        addState(n, 3);
        S.pop();

        addState(n, 4);
        if (n == end)
        {
            addState(n, 5);
            outcome = QString("Path has been found!");
            QVector<Node*> path;

            while (parent[n] != n)
            {
                addState(n, 5);
                path.push_back(n);
                n = parent[n];
            }

            path.push_back(start);
            std::reverse(std::begin(path), std::end(path));

            return;
        }

        for (auto& m : graph.getNeighbours(n))
        {
            addState(n, 6);
            if (parent.find(m) == parent.end())
            {
                addState(m, 7);
                parent[m] = n;

                S.push(m);
            }
        }
    }
    addState(start, 8);
    outcome = QString("Requested path doesn't exist!");

}