#include <iostream>
#include <iterator>
#include <set>
#include <vector>
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

std::vector<int> DFS(int start, int end, Graph* G)
{
    std::set<int> visitedNodes;
    std::vector<int> path;
    
    visitedNodes.insert(start);
    path.push_back(start);
    
    while (!path.empty())
    {
        int n = path.back();

        if (n == end)
        {
            std::cout << "Path has been found: ";
            std::copy(std::cbegin(path), std::cend(path),
                      std::ostream_iterator<int>(std::cout, " "));

            std::cout << std::endl;
            return path;
        }

        bool hasUnvisited = false;
        for (auto& m : G->getNeighbours(n))
        {
            if (visitedNodes.find(m) == visitedNodes.end())
            {
                path.push_back(m);
                visitedNodes.insert(m);
                hasUnvisited = true;
            }
        }

        if (!hasUnvisited)
            path.pop_back();
    }

    std::cout << "Requested path doesn't exist!" << std::endl;
    return std::vector<int>();
}

//int main()
//{
//    std::map<int, std::vector<int>> aList;
//    aList[1] = {2};
//    aList[2] = {1, 3};
//    aList[3] = {1};

//    Graph* G = new Graph(aList);
//    DFS(1, 3, G);

//    return 0;
//}
