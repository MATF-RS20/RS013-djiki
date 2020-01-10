#include "bfs.hpp"
#include <queue>

BFS::BFS()
    : GraphAlgorithm()
{
    definePseudocode();
}

BFS::BFS(Graph *g)
    : GraphAlgorithm(g)
{
    definePseudocode();
}

void BFS::definePseudocode()
{
    code.setInput("Graph G, starting node and target node");
    code.setOutput("Shortest path from the starting node to the target node in graph G (if such path exists)");


    code += "Put only starting node in queue S";
    code += "While queue S is not empty do";
    code += "\tTake the begining of the queue S as N";
    code += "\tIf N is the target node ";
    code += "\t\tThen inform that the path has been found and reconstruct it (going backwards from the target node)";
    code += "\tFor every descendant M of node N for which parent is not defined do";
    code += "\t\tRemember N as parent of M and add it to the end of queue S";
    code += "Inform that requested path doesn't exist";
}

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
