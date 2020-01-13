#include "dfs.hpp"
#include <QSet>

DFS::DFS()
    : GraphAlgorithm()
{
    definePseudocode();
}

DFS::DFS(Graph *g)
    : GraphAlgorithm(g)
{
    definePseudocode();
}

void DFS::definePseudocode()
{
    code.setInput("Graph G, starting node and target node");
    code.setOutput("Path from the starting node to the target node in graph G (if such path exists)");


    code += "Put starting node on stack PATH";
    code += "Insert starting node in the SET OF VISITED NODES";
    code += "While stack PATH is not empty do";
    code += "\tTake the top of the stack as N";
    code += "\tIf N is the target node ";
    code += "\t\tThen inform that the path has been found and reconstruct it from the stack PATH";
    code += "\tElse if N has no unvisited descendants";
    code += "\t\tThen remove N from stack PATH";
    code += "\tElse choose first unvisited descendant and add it on top of the stack PATH and in the SET OF VISITED NODES";
    code += "Inform that requested path doesn't exist";
}

void DFS::solve()
{
    QSet<Node*> visitedNodes;
    QVector<Node*> path;

    addState(start, 1);
    visitedNodes.insert(start);

    addState(start, 2);
    path.push_back(start);

    addState(start, 3);

    while (!path.empty())
    {

        Node* n = path.back();
        addState(n, 4);

        addState(n, 5);
        if (n == end)
        {
            addState(n, 6);
            outcome = QString("Path has been found!");

            std::reverse(std::begin(path), std::end(path));

            return;
        }

        bool hasUnvisited = false;
        for (auto& m : graph.getNeighbours(n))
        {
            if (visitedNodes.find(m) == visitedNodes.end())
            {
                addState(n, 9);
                path.push_back(m);
                visitedNodes.insert(m);
                hasUnvisited = true;
            }
        }

        if (!hasUnvisited)
        {
            addState(n, 7);
            addState(n, 8);
            path.pop_back();
        }
    }

    addState(start, 10);
    outcome = QString("Requested path doesn't exist!");

}

