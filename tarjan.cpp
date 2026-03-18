#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int UNDEFINED = -1;

struct Vertex {
    int index = UNDEFINED;
    int lowlink = UNDEFINED;
    bool onStack = false;
};

class TarjanSCC {
    int numVertices;
    std::vector<std::vector<int>>& adj;
    std::vector<Vertex> vertices;
    std::stack<int> S;
    int index = 0;
    std::vector<std::vector<int>> sccs;

    void strongconnect(int v) {
        vertices[v].index = index;
        vertices[v].lowlink = index;
        index++;
        S.push(v);
        vertices[v].onStack = true;

        for (int w : adj[v]) {
            if (vertices[w].index == UNDEFINED) {
                strongconnect(w);
                vertices[v].lowlink = std::min(vertices[v].lowlink, vertices[w].lowlink);
            } else if (vertices[w].onStack) {
                vertices[v].lowlink = std::min(vertices[v].lowlink, vertices[w].index);
            }
        }

        if (vertices[v].lowlink == vertices[v].index) {
            std::vector<int> scc;
            int w;
            do {
                w = S.top(); S.pop();
                vertices[w].onStack = false;
                scc.push_back(w);
            } while (w != v);
            sccs.push_back(scc);
        }
    }

public:
    TarjanSCC(int n, std::vector<std::vector<int>>& adjList)
        : numVertices(n), adj(adjList), vertices(n) {}

    std::vector<std::vector<int>> findSCCs() {
        for (int v = 0; v < numVertices; v++) {
            if (vertices[v].index == UNDEFINED) {
                strongconnect(v);
            }
        }
        return sccs;
    }
};

int main() {
    int n = 8;
    std::vector<std::vector<int>> adj(n);

    // Example graph
    adj[0] = {1};
    adj[1] = {2};
    adj[2] = {0};
    adj[3] = {1, 2, 4};
    adj[4] = {3, 5};
    adj[5] = {2, 6};
    adj[6] = {5};
    adj[7] = {4, 6, 7};

    TarjanSCC tarjan(n, adj);
    auto sccs = tarjan.findSCCs();

    std::cout << "Strongly Connected Components:\n";
    for (auto& scc : sccs) {
        std::cout << "{ ";
        for (int v : scc) std::cout << v << " ";
        std::cout << "}\n";
    }
    return 0;
}