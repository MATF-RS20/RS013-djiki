#include <iostream>
#include <iterator>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

class Graph {
public:
    Graph(std::map<int, std::vector<int>> lst)
        : adjacencyList(lst)
    {}

    std::vector<int> getNeighbours(int n)
    {
        return adjacencyList[n];
    }

private:
    std::map<int, std::vector<int>> adjacencyList;
};

std::vector<int> BFS(int start, int end, Graph* G)
{
    std::queue<int> S;
    S.push(start);
    std::map<int, int> parent;
    parent[start] = start;

    while (!S.empty())
    {
        int n = S.back();
        S.pop();

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
            if (parent.find(m) == parent.end())
            {
                parent[m] = n;

                S.push(m);
            }
        }
    }

    std::cout << "Requested path doesn't exist!" << std::endl;
    return std::vector<int>();
}

int main()
{
    std::map<int, std::vector<int>> aList;
    aList[1] = {2};
    aList[2] = {1, 3};
    aList[3] = {1};

    Graph* G = new Graph(aList);
    BFS(1, 3, G);

    return 0;
}
