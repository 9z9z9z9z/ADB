#include <iostream>
#include <climits>
#include <vector>

void dynamic_programming(std::vector<std::vector<int>>& matrix, int start, int end, std::vector<int>& weight) {
    int n = matrix.size();
    start--;
    end--;
    weight[start] = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (matrix[j][k] != 0 && weight[j] != INT_MAX && weight[j] + matrix[j][k] < weight[k]) {
                    weight[k] = weight[j] + matrix[j][k];
                }
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> adjacencyMatrix = {
                            {0, 6, 6, 7, 9, 0, 0},
                            {0, 0, 5, 0, 0, 5, 0},
                            {0, 0, 0, 2, 2, 0, 3},
                            {0, 0, 0, 0, 0, 0, 1},
                            {0, 0, 0, 0, 0, 4, 8},
                            {0, 0, 0, 0, 0, 0, 4},
                            {0, 0, 0, 0, 0, 0, 0} };

    std::vector<int> weight(adjacencyMatrix.size(), INT_MAX);
    dynamic_programming(adjacencyMatrix, 1, 5, weight);
    std::cout << "Shortest path with: " << 1 << " and " << 5 << " is: " << weight[4] << std::endl;

    return 0;
}
