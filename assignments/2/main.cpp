#include <fstream>
#include "graph.h"
#include "adjacencyMatrixGraph.h"

int main() {
    Graph g;
    g.insert_edge("Oslo", "fly", "Bergen");
    g.insert_edge("Bergen", "tog", "Trondheim");

    // Skriv til fil
    std::ofstream out("graf.txt");
    g.write(out);
    out.close();

    // Les fra fil
    MatrixGraph g2;
    std::ifstream in("graf.txt");
    g2.read(in);
    in.close();

    g2.disconnect("Oslo", "Bergen");
    g2.remove_node("Bergen");
}