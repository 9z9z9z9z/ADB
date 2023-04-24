#include <iostream>
#include <vector.h>

struct Edge{
    Edge() {}
    Edge(int n1, int n2, int w) {
        node1 = n1;
        node2 = n2;
        weight = w;
    }

    Edge& operator=(const Edge& rhs)
    {
        if (this == &rhs)
            return *this;
        else
        {
            node1 = rhs.node1;
            node2 = rhs.node2;
            weight = rhs.weight;
            return *this;
        }
    }

    int node1;
    int node2;
    int weight;
};

std::ostream& operator<<(std::ostream& os, const Edge& pair) {
    os << "(" << pair.node1 << ", " << pair.node2 << ", " << pair.weight << ")";
    return os;
}

bool operator==(const Edge& lhs, const Edge& rhs) {
    return lhs.weight == rhs.weight;
}

bool operator<(const Edge& lhs, const Edge& rhs) {
    return lhs.weight < rhs.weight;
}

int dynamic_prgramming(std::vector<std::vector<int>> adjacencyMatrix) {
    int path_weight = 0;
    std::vector<int> node;
    for (node : adjacencyMatrix) {
        
    }


}

int main() {
    std::vector<std::vector<int>> adjacencyMatrix = {
                            {0, 6, 6, 7, 9, 0, 0},
                            {0, 0, 5, 0, 0, 2, 0},
                            {0, 0, 0, 2, 2, 0, 3},
                            {0, 0, 0, 0, 0, 0, 1},
                            {0, 0, 0, 0, 0, 4, 8},
                            {0, 0, 0, 0, 0, 0, 4},
                            {0, 0, 0, 0, 0, 0, 0} };


    return 0;
}
