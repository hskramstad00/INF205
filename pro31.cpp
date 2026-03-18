// Bruk: ./pro31 [--verbose|--silent] [--matrix] <grafil>
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include "scc.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool verbose    = true;
    bool use_matrix = false;
    std::string filename;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if      (arg == "--verbose") verbose = true;
        else if (arg == "--silent")  verbose = false;
        else if (arg == "--matrix")  use_matrix = true;
        else                         filename = arg;
    }

    if (filename.empty()) {
        std::cerr << "Bruk: " << argv[0] << " [--verbose|--silent] [--matrix] <grafil>\n";
        return 1;
    }

    std::ifstream inn(filename);
    if (!inn) { std::cerr << "Kan ikke aapne '" << filename << "'\n"; return 1; }

    Graph* g = use_matrix
        ? static_cast<Graph*>(new MatrixGraph())
        : static_cast<Graph*>(new IncidenceGraph());
    g->read(inn);
    inn.close();

    if (verbose) {
        std::cout << "Graf lest fra '" << filename << "' ("
                  << (use_matrix ? "matrisebasert" : "insidensliste") << ")\n\nKanter:\n";
        g->write(std::cout);
        std::cout << "\n";
    }

    auto sccs = find_sccs(*g);

    if (verbose) {
        std::cout << "Sterkt sammenhengende komponenter (" << sccs.size() << " stk):\n";
        int nr = 1;
        for (const auto& scc : sccs) {
            std::cout << "  SCC " << nr++ << ": { ";
            for (const auto& node : scc) std::cout << node << " ";
            std::cout << "}\n";
        }
    } else {
        std::cout << sccs.size() << "\n";
    }

    delete g;
    return 0;
}