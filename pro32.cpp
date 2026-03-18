// Bruk: ./pro32 [--verbose|--silent] [--matrix] <grafil> <spørrefil>
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include "diamond.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool verbose    = true;
    bool use_matrix = false;
    std::string graphfile, queryfile;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if      (arg == "--verbose") verbose = true;
        else if (arg == "--silent")  verbose = false;
        else if (arg == "--matrix")  use_matrix = true;
        else if (graphfile.empty())  graphfile = arg;
        else                         queryfile = arg;
    }

    if (graphfile.empty() || queryfile.empty()) {
        std::cerr << "Bruk: " << argv[0]
                  << " [--verbose|--silent] [--matrix] <grafil> <spørrefil>\n";
        return 1;
    }

    std::ifstream ginn(graphfile);
    if (!ginn) { std::cerr << "Kan ikke aapne '" << graphfile << "'\n"; return 1; }

    Graph* g = use_matrix
        ? static_cast<Graph*>(new MatrixGraph())
        : static_cast<Graph*>(new IncidenceGraph());
    g->read(ginn);
    ginn.close();

    std::ifstream qinn(queryfile);
    if (!qinn) { std::cerr << "Kan ikke aapne '" << queryfile << "'\n"; return 1; }
    DiamondQuery q = read_query(qinn);
    qinn.close();

    if (verbose) {
        std::cout << "Graf lest fra '" << graphfile << "' ("
                  << (use_matrix ? "matrisebasert" : "insidensliste") << ")\nKanter:\n";
        g->write(std::cout);
        std::cout << "\nSpaerring (jevn-sti):  ";
        for (const auto& l : q.even_labels) std::cout << l << " ";
        std::cout << "\nSpaerring (odde-sti):  ";
        for (const auto& l : q.odd_labels)  std::cout << l << " ";
        std::cout << "\n\n";
    }

    auto pairs = find_diamond_pairs(*g, q);

    if (verbose) {
        std::cout << "Diamantpar funnet (" << pairs.size() << " stk):\n";
        for (const auto& [ni, nj] : pairs)
            std::cout << "  " << ni << " -> " << nj << "\n";
    } else {
        std::cout << pairs.size() << "\n";
    }

    delete g;
    return 0;
}