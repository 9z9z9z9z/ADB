#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

const int INF = INT_MAX;

class BranchAndBoundTSP {
private:
    int n;
    int startNode;
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;
    int optimalCost;
    std::vector<int> optimalPath;

public:
    BranchAndBoundTSP(const std::vector<std::vector<int>>& adjacencyMatrix) {
        graph = adjacencyMatrix;
        n = graph.size();
        visited.resize(n, false);
        optimalCost = INF;
    }

    void solve() {
        std::vector<int> path;
        path.push_back(0);
        visited[0] = true;
        startNode = 0;
        branchAndBound(path, 0, 0, 1);
    }

    void branchAndBound(std::vector<int>& path, int cost, int level, int count) {
        if (count == n) {
            if (graph[level][startNode] != INF && cost + graph[level][startNode] < optimalCost) {
                path.push_back(startNode);
                optimalPath = path;
                optimalCost = cost + graph[level][startNode];
                path.pop_back();
            }
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && graph[level][i] != INF) {
                visited[i] = true;
                path.push_back(i);
                branchAndBound(path, cost + graph[level][i], i, count + 1);
                path.pop_back();
                visited[i] = false;
            }
        }
    }

    int getOptimalCost() const {
        return optimalCost;
    }

    std::vector<int> getOptimalPath() const {
        return optimalPath;
    }
};

int main() {
    std::vector<std::vector<int>> adjacencyMatrix = {
            {0, 68, 73, 24, 70, 9},
            {58, 0, 16, 44, 11, 92},
            {63, 9, 0, 86, 13, 18},
            {17, 34, 76, 0, 52, 70},
            {60, 18, 3, 45, 0, 58},
            {16, 82, 11, 60, 48, 0}
    };

    BranchAndBoundTSP tsp(adjacencyMatrix);
    tsp.solve();

    std::cout << "Optimal Cost: " << tsp.getOptimalCost() << std::endl;
    std::cout << "Optimal Path: ";
    std::vector<int> optimalPath = tsp.getOptimalPath();
    for (int node : optimalPath) {
        std::cout << node + 1 << " ";
    }
    std::cout << std::endl;

    return 0;
}
