#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include <iostream>

int main() {
    std::cout << "=== MatrixGraph: disconnect Oslo->Bergen ===\n";
    MatrixGraph mg;
    mg.insert_edge("Oslo",   "fly",  "Bergen");
    mg.insert_edge("Bergen", "tog",  "Trondheim");
    mg.insert_edge("Oslo",   "buss", "Bergen");
    mg.insert_edge("Oslo",   "bil",  "Trondheim");
    std::cout << "Foer disconnect:\n"; mg.write(std::cout);
    mg.disconnect("Oslo", "Bergen");
    std::cout << "Etter disconnect(Oslo, Bergen):\n"; mg.write(std::cout);

    std::cout << "\n=== IncidenceGraph: remove_node Bergen ===\n";
    IncidenceGraph ig;
    ig.insert_edge("Oslo",      "fly",  "Bergen");
    ig.insert_edge("Bergen",    "tog",  "Trondheim");
    ig.insert_edge("Stavanger", "buss", "Oslo");
    std::cout << "Foer remove_node:\n"; ig.write(std::cout);
    ig.remove_node("Bergen");
    std::cout << "Etter remove_node(Bergen):\n"; ig.write(std::cout);
    return 0;
}