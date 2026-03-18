#include "incidenceListGraph.h"
#include <fstream>
#include <iostream>

int main() {
    IncidenceGraph g;
    g.insert_edge("Oslo",    "fly",  "Bergen");
    g.insert_edge("Bergen",  "tog",  "Trondheim");
    g.insert_edge("Oslo",    "bil",  "Trondheim");
    g.insert_edge("Oslo",    "fly",  "Oslo");
    g.insert_edge("Oslo",    "buss", "Bergen");

    std::ofstream ut("demo22_output.txt");
    g.write(ut);
    ut.close();
    std::cout << "Graf skrevet til demo22_output.txt\n";

    IncidenceGraph g2;
    std::ifstream inn("demo22_output.txt");
    g2.read(inn);
    inn.close();
    std::cout << "Graf lest tilbake:\n";
    g2.write(std::cout);
    return 0;
}