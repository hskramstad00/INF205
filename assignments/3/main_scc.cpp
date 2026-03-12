/**
 * main_scc.cpp – Problem 3.1: Strongly connected components via Tarjan's algorithm.
 *
 * Usage:
 *   ./scc [-v|-s] [-m incidence|matrix] <graph_file>
 *
 * Flags:
 *   -v   verbose  (print every SCC, default)
 *   -s   silent   (print only SCC count and sizes)
 *   -m incidence  use IncidenceGraph  (default)
 *   -m matrix     use MatrixGraph
 */
#include "graph.h"
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include "scc.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <memory>
#include <string>

int main(int argc, char** argv) {
    // ── Parse command line ───────────────────────────────────────────────────
    bool verbose = true;
    std::string graph_file;
    std::string mode = "incidence";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-v") { verbose = true; }
        else if (arg == "-s") { verbose = false; }
        else if (arg == "-m" && i + 1 < argc) {
            mode = argv[++i];
        } else {
            graph_file = arg;
        }
    }

    if (graph_file.empty()) {
        std::cerr << "Usage: " << argv[0]
                  << " [-v|-s] [-m incidence|matrix] <graph_file>\n";
        return 1;
    }

    // ── Build graph ──────────────────────────────────────────────────────────
    std::unique_ptr<Graph> g;
    if (mode == "matrix") g = std::make_unique<MatrixGraph>();
    else                  g = std::make_unique<IncidenceGraph>();

    std::ifstream in(graph_file);
    if (!in) { std::cerr << "Cannot open: " << graph_file << "\n"; return 1; }
    g->read(in);

    if (verbose)
        std::cout << "Graph loaded from \"" << graph_file
                  << "\" using " << mode << " representation.\n"
                  << "Nodes: " << g->nodes().size() << "\n\n";

    // ── Run Tarjan's SCC ─────────────────────────────────────────────────────
    auto t0 = std::chrono::high_resolution_clock::now();
    auto sccs = tarjan_scc(*g, verbose);
    auto t1 = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    // Summary (always printed)
    std::cout << "\nSummary: " << sccs.size() << " SCC(s) found.\n";
    std::size_t trivial = 0;
    for (const auto& scc : sccs) if (scc.size() == 1) ++trivial;
    std::cout << "  Trivial (size 1): " << trivial << "\n";
    std::cout << "  Non-trivial:      " << sccs.size() - trivial << "\n";
    std::cout << "  Time: " << ms << " ms\n";

    return 0;
}
