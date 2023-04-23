#include <iostream>
#include <valarray>
#include <stack>
#include <vector>
#include <climits>

std::string analyze(std::basic_string<char> str) {
    std::stack<char> steck;
    int size = str.size();
    char a;
    try {
        for (int i = 0; i < size; i++) {
            a = str[i];
            if (a == '(') steck.push(a);
            else if (a == ')') steck.pop();
        }
    }
    catch (const std::exception) {
        return "Fatal error";
    }
    if (steck.empty()) return "Your input is correct";
    else return "Invalid operation";
}

int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

double* generate(int N) {
    double* ret = new double[N];
    for (int i = 1; i < N + 1; i++) {
        ret[i - 1] = static_cast<double>(factorial(i)) / static_cast<double>(pow(2, i - 1));
    }
    return ret;
}

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


int find_place(const std::vector<std::vector<int>>& v, int node) {
    for (int i = 0; i < v.size(); i++) {
        auto it = std::find(v[i].begin(), v[i].end(), node);
        if (it != v[i].end()) {
            return i;
        }
    }
    return 0;
}

void Union(std::vector<std::vector<int>>& v, int idx1, int idx2) {
    std::vector<int> dist(v[idx1].size() + v[idx2].size());
    std::set_union(v[idx1].begin(), v[idx1].end(),
                   v[idx2].begin(), v[idx2].end(), dist.begin());
    v[idx1] = {};
    v[idx2] = {};
    v.erase(std::remove(v.begin(), v.end(), v[idx1]), v.end());
    v.push_back(dist);
}

void print_array(const std::vector<std::vector<int>>& arrays) {
    for (const auto& arr : arrays) {
        std::cout << "{ ";
        for (int i : arr)
            std::cout << i << ' ';
        std::cout << "}\t";
    }
}

bool is_valid_edge(int u, int v, std::vector<bool> selected) {
    if (u == v)
        return false;
    if (selected[u] == false && selected[v] == false) return false;
    else if (selected[u] == true && selected[v] == true) return false;
    return true;
}

void prim_algorithm(const std::vector<std::vector<int>>& adjacencyMatrix) {
    int sz = adjacencyMatrix.size();
    std::vector<bool> selected(sz, false);
    selected[0] = true;
    int edge_count = 0, min_weight = 0;
    while (edge_count < sz - 1) {
        int min = INT_MAX, a = -10, b = -10;
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) { // j = i+1
                if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] < min) {
                    if (is_valid_edge(i, j, selected)) {
                        min = adjacencyMatrix[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (a != -10 && b != -10) {
            std::cout << "Edge " << ++edge_count;
            std::cout << ":(" << a << ", " << b << ", "<< min << ")" << std::endl;
            min_weight = min_weight + min;
            selected[b] = selected[a] = true;
        }
    }
    std::cout << "\nMinimum weight=" << min_weight << "\n";
}

int kruskal_algorithm(std::vector<Edge>& edges, std::vector<std::vector<int>>& v) {
    int min_weight = 0;
    std::sort(edges.begin(), edges.end());
    for (const auto& e : edges) {
        int idx1 = find_place(v, e.node1);
        int idx2 = find_place(v, e.node2);
        if (idx1 == idx2) {
            continue;
        }
        min_weight += e.weight;
        Union(v, idx1, idx2);
        // print_array(v);
        // std::cout << std::endl;
    }
    return min_weight;
}

int main() {
    std::cout << "==============  Lab3, Task3  ==============" << std::endl;
    std::string str;
    std::cout << "Input string:" << std::endl;
    std::cin >> str;
    std::cout << analyze(str) << std::endl;
    std::cout << "==============  Lab3, Task4  ==============" << std::endl;
    int n = 5;
    std::cout << "an= " << (factorial(n)) / pow(2, n - 1) << std::endl;
    std::cout << "==============  Lab4, Task6  ==============" << std::endl;
    double* base = generate(10);
    for (int i = 0; i < 10; i++) {
        std::cout << base[i] << "  ";
    }
    std::cout << "\n==============  Lab4  ==============" << std::endl;
    std::cout << "============== Kruskal's algorithm ==============" << std::endl;
    std::vector<std::vector<int>> v = { {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8} };
    std::vector<Edge> pairs = {Edge(4, 7, 1),
                               Edge(4, 6, 1),
                               Edge(5, 7, 2),
                               Edge(5, 8, 2),
                               Edge(3, 5, 2),
                               Edge(1, 6, 3),
                               Edge(1, 2, 4),
                               Edge(2, 5, 5),
                               Edge(6, 7, 5),
                               Edge(1, 3, 6),
                               Edge(1, 4, 6),
                               Edge(3, 8, 7),
                               Edge(4, 5, 7),
                               Edge(1, 5, 8) };

    auto min_weight = kruskal_algorithm(pairs, v);
    std::cout << "Minimal weight = " << min_weight << std::endl;
    std::vector<std::vector<int>> adjacencyMatrix = {
                        {0, 4, 6, 6, 8, 3, 0, 0},
                        {4, 0, 0, 0, 5, 0, 0, 0},
                        {6, 0, 0, 0, 2, 0, 0, 7},
                        {6, 0, 0, 0, 7, 1, 1, 0},
                        {8, 5, 3, 7, 0, 0, 2, 2},
                        {3, 0, 0, 1, 0, 0, 5, 0},
                        {0, 0, 0, 1, 2, 5, 0, 9},
                        {0, 0, 7, 0, 2, 0, 9, 0}
    };
    std::vector<Edge> pairs_for_prim;
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = i + 1; j < adjacencyMatrix.size(); j++) {
            if (adjacencyMatrix[i][j] != 0) {
                pairs_for_prim.emplace_back(i + 1, j + 1, adjacencyMatrix[i][j]);
            }
        }
    }
    for (const auto& el : pairs_for_prim) {
        std::cout << el << std::endl;
    }
//    std::cout << "============== Kruskal's algorithm ==============" << std::endl;
//    min_weight = kruskal_algorithm(pairs_for_prim, v);
//    std::cout << "Kruskal weight = " << min_weight << std::endl;
    std::cout << "============== Prim's algorithm ==============" << std::endl;
    prim_algorithm(adjacencyMatrix);
    return 0;
}
