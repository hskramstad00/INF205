#include "scc.h"
#include <iostream>
#include <stack>
#include <unordered_map>

/*
 * Iterative Tarjan's SCC (avoids call-stack overflow on large graphs).
 *
 * Each "frame" on the explicit stack corresponds to a DFS call for a node.
 * We store the iterator position so we can resume after returning from a
 * recursive sub-call.
 */

struct TarjanFrame {
    std::string node;
    std::vector<std::pair<std::string,std::string>> edges;  // out-edges snapshot
    std::size_t edge_idx;  // next edge to process
};

std::vector<std::vector<std::string>>
tarjan_scc(const Graph& g, bool verbose) {
    const auto all_nodes = g.nodes();

    std::unordered_map<std::string, int>  index_map;
    std::unordered_map<std::string, int>  lowlink_map;
    std::unordered_map<std::string, bool> on_stack_map;

    std::stack<std::string>  tarjan_stack;   // the "S" stack in Tarjan's
    std::vector<std::vector<std::string>> sccs;

    int counter = 0;

    // Iterative DFS – one call per unvisited node
    for (const auto& start : all_nodes) {
        if (index_map.count(start)) continue;  // already visited

        // DFS call stack
        std::stack<TarjanFrame> call_stack;
        {
            TarjanFrame f;
            f.node     = start;
            f.edges    = g.out_edges(start);
            f.edge_idx = 0;
            index_map[start]   = counter;
            lowlink_map[start] = counter;
            on_stack_map[start] = true;
            tarjan_stack.push(start);
            ++counter;
            call_stack.push(std::move(f));
        }

        while (!call_stack.empty()) {
            TarjanFrame& frame = call_stack.top();

            if (frame.edge_idx < frame.edges.size()) {
                // Process next child edge
                const std::string& w = frame.edges[frame.edge_idx].second;
                ++frame.edge_idx;

                if (!index_map.count(w)) {
                    // Tree edge – recurse into w
                    index_map[w]    = counter;
                    lowlink_map[w]  = counter;
                    on_stack_map[w] = true;
                    tarjan_stack.push(w);
                    ++counter;

                    TarjanFrame child;
                    child.node     = w;
                    child.edges    = g.out_edges(w);
                    child.edge_idx = 0;
                    call_stack.push(std::move(child));
                } else if (on_stack_map[w]) {
                    // Back/cross edge to a node still on the stack
                    lowlink_map[frame.node] =
                        std::min(lowlink_map[frame.node], index_map[w]);
                }
                // If w is already finished (not on stack) → nothing to do
            } else {
                // All children processed – pop this frame
                const std::string v = frame.node;
                call_stack.pop();

                if (!call_stack.empty()) {
                    // Propagate lowlink to parent
                    const std::string& parent = call_stack.top().node;
                    lowlink_map[parent] =
                        std::min(lowlink_map[parent], lowlink_map[v]);
                }

                // Is v the root of an SCC?
                if (lowlink_map[v] == index_map[v]) {
                    std::vector<std::string> scc;
                    while (true) {
                        std::string w = tarjan_stack.top();
                        tarjan_stack.pop();
                        on_stack_map[w] = false;
                        scc.push_back(w);
                        if (w == v) break;
                    }
                    sccs.push_back(std::move(scc));
                }
            }
        }
    }

    if (verbose) {
        std::cout << "Strongly connected components (" << sccs.size() << " total):\n";
        for (std::size_t i = 0; i < sccs.size(); ++i) {
            std::cout << "  SCC " << i + 1 << " [" << sccs[i].size() << " node(s)]: ";
            for (std::size_t j = 0; j < sccs[i].size(); ++j) {
                if (j) std::cout << ", ";
                std::cout << sccs[i][j];
            }
            std::cout << "\n";
        }
    }

    return sccs;
}
