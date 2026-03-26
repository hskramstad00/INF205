#include "graph.h"
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include "diamond.h"

#include <fstream>
#include <iostream>
#include <chrono>
#include <memory>
#include <string>

int main(int argc, char** argv) {
    bool verbose = true;
    std::string graph_file, query_file;
    std::string mode = "incidence";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-v") { verbose = true; }
        else if (arg == "-s") { verbose = false; }
        else if (arg == "-m" && i + 1 < argc) {
            mode = argv[++i];
        } else if (graph_file.empty()) {
            graph_file = arg;
        } else {
            query_file = arg;
        }
    }

    if (graph_file.empty() || query_file.empty()) {
        std::cerr << "Usage: " << argv[0]
                  << " [-v|-s] [-m incidence|matrix] <graph_file> <query_file>\n";
        return 1;
    }

    std::unique_ptr<Graph> g;
    if (mode == "matrix") g = std::make_unique<MatrixGraph>();
    else                  g = std::make_unique<IncidenceGraph>();

    std::ifstream gin(graph_file);
    if (!gin) { std::cerr << "Cannot open graph: " << graph_file << "\n"; return 1; }
    g->read(gin);

    std::vector<std::string> path1, path2;
    std::ifstream qin(query_file);
    if (!qin) { std::cerr << "Cannot open query: " << query_file << "\n"; return 1; }
    read_query(qin, path1, path2);

    if (verbose) {
        std::cout << "Graph:  " << graph_file
                  << " (" << g->nodes().size() << " nodes, "
                  << mode << " representation)\n";
        std::cout << "Path 1 labels (" << path1.size() << "): ";
        for (const auto& l : path1) std::cout << l << " ";
        std::cout << "\nPath 2 labels (" << path2.size() << "): ";
        for (const auto& l : path2) std::cout << l << " ";
        std::cout << "\n\n";
    }

    auto t0 = std::chrono::high_resolution_clock::now();
    auto pairs = diamond_query(*g, path1, path2, verbose);
    auto t1 = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    std::cout << "\nDiamond pairs found: " << pairs.size() << "\n";
    std::cout << "Time: " << ms << " ms\n";

    return 0;
}
