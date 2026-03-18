#include "scc.h"
#include <iostream>
#include <stack>
#include <unordered_map>

// ── State delt på tvers av alle rekursive kall ────────────────────────────
struct TarjanState {
    std::unordered_map<std::string, int>  index_map;
    std::unordered_map<std::string, int>  lowlink_map;
    std::unordered_map<std::string, bool> on_stack_map;
    std::stack<std::string>               tarjan_stack;
    std::vector<std::vector<std::string>> sccs;
    int counter = 0;
};

// ── Rekursiv DFS-hjelper ──────────────────────────────────────────────────
static void strongconnect(const Graph& g,
                           const std::string& v,
                           TarjanState& s) {
    // Initialiser node v
    s.index_map[v]   = s.counter;
    s.lowlink_map[v] = s.counter;
    s.on_stack_map[v] = true;
    s.tarjan_stack.push(v);
    ++s.counter;

    // Behandle alle utgående kanter
    for (const auto& [edge_lbl, w] : g.out_edges(v)) {
        if (!s.index_map.count(w)) {
            // Tree edge – rekurser ned i w
            strongconnect(g, w, s);
            // Etter retur: propagér lowlink opp
            s.lowlink_map[v] = std::min(s.lowlink_map[v], s.lowlink_map[w]);
        } else if (s.on_stack_map[w]) {
            // Back-edge til node som fortsatt er på stacken
            s.lowlink_map[v] = std::min(s.lowlink_map[v], s.index_map[w]);
        }
    }

    // Er v roten av en SCC?
    if (s.lowlink_map[v] == s.index_map[v]) {
        std::vector<std::string> scc;
        while (true) {
            std::string w = s.tarjan_stack.top();
            s.tarjan_stack.pop();
            s.on_stack_map[w] = false;
            scc.push_back(w);
            if (w == v) break;
        }
        s.sccs.push_back(std::move(scc));
    }
}

// ── Offentlig funksjon ───────────────────────────
std::vector<std::vector<std::string>>
tarjan_scc(const Graph& g, bool verbose) {
    TarjanState s;

    for (const auto& node : g.nodes())
        if (!s.index_map.count(node))
            strongconnect(g, node, s);

    if (verbose) {
        std::cout << "Strongly connected components ("
                  << s.sccs.size() << " total):\n";
        for (std::size_t i = 0; i < s.sccs.size(); ++i) {
            std::cout << "  SCC " << i + 1
                      << " [" << s.sccs[i].size() << " node(s)]: ";
            for (std::size_t j = 0; j < s.sccs[i].size(); ++j) {
                if (j) std::cout << ", ";
                std::cout << s.sccs[i][j];
            }
            std::cout << "\n";
        }
    }

    return s.sccs;
}