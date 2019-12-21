#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <cmath>
#include <algorithm>

class Graph {
public:
    Graph(std::map<int, std::vector<std::pair<int, int>>> lst)
        : adjacencyList(lst)
    {}

    std::vector<std::pair<int, int>> getNeighbours(int n)
    {
        return adjacencyList[n];
    }

    std::map<int, std::vector<std::pair<int, int>>> adjacencyList;
};

std::vector<int> Dijkstra(int start, int end, Graph* G)
{
    std::set<int> Q;
    std::map<int, double> D;
    std::map<int, int> parent;
    parent[start] = start;

    for (auto& pair: G->adjacencyList)
    {
        Q.insert(pair.first);
        D[pair.first] = std::numeric_limits<double>::infinity();
    }

    D[start] = 0;

    while (Q.size() > 0)
    {
        int n = *Q.begin();
        for (auto& w : Q)
            if (std::fabs(D[w] - std::numeric_limits<double>::infinity()) < 0.001 && D[w] < D[n])
                n = w;

        if (std::fabs(D[n] - std::numeric_limits<double>::infinity()) < 0.001)
        {
            std::cout << "Requested path doesn't exist!" << std::endl;
            return std::vector<int>();
        }

        if (n == end)
        {
            std::cout << "Path has been found: ";
            std::vector<int> path;

            while (parent[n] != n)
            {
                path.push_back(n);
                n = parent[n];
            }

            path.push_back(start);

            std::reverse(std::begin(path), std::end(path));

            std::copy(std::cbegin(path), std::cend(path),
                      std::ostream_iterator<int>(std::cout, " "));

            std::cout << std::endl;
            return path;
        }

        for (auto& m : G->getNeighbours(n))
        {
            if (std::fabs(D[m.first] - std::numeric_limits<double>::infinity()) < 0.001
                || D[n] + m.second < D[m.first])
            {
                D[m.first] = D[n] + m.second;
                parent[m.first] = n;
            }
        }

        Q.erase(n);
    }

    std::cout << "Requested path doesn't exist!" << std::endl;
    return std::vector<int>();
}

int main()
{
    std::map<int, std::vector<std::pair<int, int>>> aList;
    aList[1] = {std::make_pair<int, int>(4, 100),
                std::make_pair<int, int>(3, 10),
                std::make_pair<int, int>(2, 5)};
    aList[2] = {std::make_pair<int, int>(3, 2)};
    aList[3] = {};
    aList[4] = {std::make_pair<int, int>(3, 5)};

    Graph* G = new Graph(aList);
    Dijkstra(1, 3, G);

    return 0;
}
