#include "dijkstra.hpp"
#include <cmath>
#include <QMap>
#include <QSet>

Dijkstra::Dijkstra()
    : GraphAlgorithm()
{
    definePseudocode();
}

Dijkstra::Dijkstra(Graph *g)
    : GraphAlgorithm(g)
{
    definePseudocode();
}

void Dijkstra::definePseudocode()
{
    code.setInput("Graph G, starting node and target node");
    code.setOutput("Shortest path from the starting node to the target node in graph G (if such path exists)");


    code += "Put all nodes from graph G in set Q";
    code += "While Q is not empty do";
    code += "\tFind node N from Q which has with the smallest found distance to the starting node and delete it from Q";
    code += "\tIf N is the target node ";
    code += "\t\tThen inform that the path has been found and reconstruct it (going backwards from the target node)";
    code += "\tFor every node M from Q which is direct neighbour of N do";
    code += "\t\tIf current distance from the starting node to M is bigger than distance from the starting node to M over node N ";
    code += "\t\t\tThen change parent of node M to N and remember new distance";
    code += "Inform that requested path doesn't exist (Q is empty and path was not found)";
}

void Dijkstra::solve()
{

    QSet<Node*> Q;
    QMap<Node*, double> D;
    QMap<Node*, Node*> parent;
    parent[start] = start;

    for (auto& node: graph.getNodes())
    {
        addState(node, 1);
        Q.insert(node);
        D[node] = std::numeric_limits<double>::infinity();
    }

    D[start] = 0;

    while (Q.size() > 0)
    {
        Node* n = *Q.begin();
        addState(n, 2);

        addState(n, 3);
        Q.erase(Q.find(n));

        for (auto &w : Q)
        {
            addState(w, 2);
            if (std::fabs(D[w] - std::numeric_limits<double>::infinity()) < 0.001 && D[w] < D[n])
                n = w;
        }

        if (std::fabs(D[n] - std::numeric_limits<double>::infinity()) < 0.001)
        {
            outcome = QString("Requested path doesn't exist!");
            return;
        }

        addState(n, 4);
        if (n == end)
        {
            outcome = QString("Path has been found!");
            std::vector<Node*> path;

            while (parent[n] != n)
            {
                addState(n, 5);
                path.push_back(n);
                n = parent[n];
            }

            path.push_back(start);
            addState(start, 5);
            std::reverse(std::begin(path), std::end(path));

            return;
        }


        for (auto m : graph.getNeighboursWeighted(n).toStdMap())
        {
            addState(n, 6);
            addState(m.first, 7);
            if (std::fabs(D[m.first] - std::numeric_limits<double>::infinity()) < 0.001
                || D[n] + m.second < D[m.first])
            {
                addState(m.first, 8);
                D[m.first] = D[n] + m.second;
                parent[m.first] = n;
            }
        }
    }

    addState(start, 9);
    outcome = QString("Requested path doesn't exist!");

}

