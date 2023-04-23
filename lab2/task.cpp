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

struct Pair{
    Pair() {

    }

    Pair(int n1, int n2, int w) {
        node1 = n1;
        node2 = n2;
        weight = w;
    }

    Pair& operator=(const Pair& rhs)
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

std::ostream& operator<<(std::ostream& os, const Pair& pair) {
    os << "(" << pair.node1 << ", " << pair.node2 << ", " << pair.weight << ")";
    return os;
}

bool operator==(const Pair& lhs, const Pair& rhs) {
    return lhs.weight == rhs.weight;
}

bool operator<(const Pair& lhs, const Pair& rhs) {
    return lhs.weight < rhs.weight;
}


int find_place(const std::vector<std::vector<int>>& v, int node) {
    for (int i = 0; i < v.size(); i++) {
        auto it = std::find(v[i].begin(), v[i].end(), node);
        if (it != v[i].end()) {
            return i;
        }
    }
    return -1;
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

void prim_algorithm(const std::vector<std::vector<int>>& adjencyMtrx) {
    int sz = adjencyMtrx.size();
    std::vector<bool> selected(sz, false);
    selected[0] = true;

    int edge_count = 0, min_weight = 0;
    while (edge_count < sz - 1) {

        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) { // j = i+1
                if (adjencyMtrx[i][j] != 0 && adjencyMtrx[i][j] < min) {
                    if (is_valid_edge(i, j, selected)) {
                        min = adjencyMtrx[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (a != -1 && b != -1) {
            std::cout << "Edge " << edge_count++;
            std::cout << ":(" << a << ", " << b << ")weight: ";
            std::cout << min << "\n";
            min_weight = min_weight + min;
            selected[b] = selected[a] = true;
        }
    }
    std::cout << "\nMinimum weight=" << min_weight << "\n";
}

int kruskal_algorithm(std::vector<Pair>& pairs, std::vector<std::vector<int>>& v) {
    int min_weight = 0;
    std::sort(pairs.begin(), pairs.end());
    for (const auto& p : pairs) {
        int idx1 = find_place(v, p.node1);
        int idx2 = find_place(v, p.node2);
        if (idx1 == idx2) {
            continue;
        }
        min_weight += p.weight;
        Union(v, idx1, idx2);
        print_array(v);
        std::cout << std::endl;
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
    std::vector<std::vector<int>> v = { {1}, {2}, {3}, {4}, {5}, {6} };
    std::vector<Pair> pairs = { Pair(2, 3, 1),
                                Pair(4, 6, 1),
                                Pair(1, 4, 2),
                                Pair(3, 4, 2),
                                Pair(2, 4, 2),
                                Pair(3, 5, 3)
    };
    auto min_weight = kruskal_algorithm(pairs, v);
    std::cout << "min_weight = " << min_weight << std::endl;


    std::cout << "============== Prim's algorithm ==============" << std::endl;
    std::vector<std::vector<int>> adjacencyMatrix = {
                        {0, 0, 0, 2, 0, 0},
                        {0, 0, 1, 2, 0, 0},
                        {0, 1, 0, 2, 3, 0},
                        {2, 2, 2, 0, 0, 1},
                        {0, 0, 3, 0, 0, 0},
                        {0, 0, 0, 1, 0, 0} };
    prim_algorithm(adjacencyMatrix);

    std::vector<std::vector<int>> adjacencyMatrixVar5 = {
            {0, 4, 6, 6, 8, 3, 0, 0},
            {4, 0, 0, 0, 5, 0, 0, 0},
            {6, 0, 0, 0, 2, 0, 0, 7},
            {6, 0, 0, 0, 7, 1, 1, 0},
            {8, 5, 3, 7, 0, 0, 2, 2},
            {3, 0, 0, 1, 0, 0, 5, 0},
            {0, 0, 0, 1, 2, 5, 0, 9},
            {0, 0, 7, 0, 2, 0, 9, 0}
    };

    std::vector<Pair> pairs_var5;
    std::vector<std::vector<int>> v_var5 = { {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8} };

    for (int i = 0; i < adjacencyMatrixVar5.size(); i++) {
        for (int j = i + 1; j < adjacencyMatrixVar5.size(); j++) {
            if (adjacencyMatrixVar5[i][j] != 0) {
                pairs_var5.emplace_back(Pair(i+1, j+1, adjacencyMatrixVar5[i][j]));
            }
        }
    }

    for (const auto& el : pairs_var5)
    {
        std::cout << el << std::endl;
    }
    std::cout << "============== Kruskal's algorithm ==============" << std::endl;
    auto min_weight_var5 = kruskal_algorithm(pairs_var5, v_var5);
    std::cout << "Kruskal min_weight_var5 = " << min_weight_var5 << std::endl;
    std::cout << "============== Prim's algorithm ==============" << std::endl;
    prim_algorithm(adjacencyMatrixVar5);
    std::cout << "==============  Lab4, Task4  ==============" << std::endl;

    std::cout << "==============  Lab4, Task6  ==============" << std::endl;
    return 0;
}
