#include "graph.h"
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include <fstream>
#include <iostream>

// Hjelpefunksjon for å printe tydelige seksjoner
void seksjon(const std::string& tittel) {
    std::cout << "\n========== " << tittel << " ==========\n";
}

int main() {

    // ================================================
    // OPPGAVE 2.1 – Insidensliste: insert_edge
    // ================================================
    seksjon("2.1 IncidenceGraph: insert_edge");
    IncidenceGraph ig;
    ig.insert_edge("Oslo",      "fly",  "Bergen");
    ig.insert_edge("Bergen",    "tog",  "Trondheim");
    ig.insert_edge("Oslo",      "bil",  "Trondheim");
    ig.insert_edge("Oslo",      "fly",  "Oslo");     // samme start og mål – skal være lov
    ig.insert_edge("Oslo",      "buss", "Bergen");   // flere kanter mellom samme noder – skal være lov
    ig.write(std::cout);

    // ================================================
    // OPPGAVE 2.2 – Fil I/O: skriv og les
    // ================================================
    seksjon("2.2 Fil-I/O: skriv til fil");
    std::ofstream ut("graf.txt");
    ig.write(ut);
    ut.close();
    std::cout << "Skrevet til graf.txt\n";

    seksjon("2.2 Fil-I/O: les fra fil inn i ny graf");
    IncidenceGraph ig_fra_fil;
    std::ifstream inn("graf.txt");
    ig_fra_fil.read(inn);
    inn.close();
    ig_fra_fil.write(std::cout);

    // ================================================
    // OPPGAVE 2.3 – Abstrakt klasse: bruk Graph*
    // ================================================
    seksjon("2.3 Abstrakt grensesnitt via Graph*");
    Graph* abstrakt = new IncidenceGraph();
    abstrakt->insert_edge("A", "kant1", "B");
    abstrakt->insert_edge("B", "kant2", "C");
    abstrakt->write(std::cout);
    delete abstrakt;

    // ================================================
    // OPPGAVE 2.4 – Matrisebasert: MatrixGraph
    // ================================================
    seksjon("2.4 MatrixGraph: insert_edge");
    MatrixGraph mg;
    mg.insert_edge("Oslo",   "fly",  "Bergen");
    mg.insert_edge("Bergen", "tog",  "Trondheim");
    mg.insert_edge("Oslo",   "buss", "Bergen");   // flere kanter samme nodpar
    mg.insert_edge("Oslo",   "fly",  "Oslo");     // løkke
    mg.write(std::cout);

    // ================================================
    // OPPGAVE 2.5 – Slette kanter og noder
    // ================================================
    seksjon("2.5 disconnect: fjern alle kanter Oslo->Bergen");
    mg.disconnect("Oslo", "Bergen");
    mg.write(std::cout);
    // Oslo har nå bare kant til seg selv, Bergen har kant til Trondheim

    seksjon("2.5 remove_node: fjern Bergen");
    IncidenceGraph ig2;
    ig2.insert_edge("Oslo",      "fly",  "Bergen");
    ig2.insert_edge("Bergen",    "tog",  "Trondheim");
    ig2.insert_edge("Stavanger", "buss", "Oslo");
    std::cout << "Før remove_node:\n";
    ig2.write(std::cout);
    ig2.remove_node("Bergen");
    std::cout << "Etter remove_node(Bergen) – isolerte noder skal også forsvinne:\n";
    ig2.write(std::cout);

    // ================================================
    // OPPGAVE 2.6 – Femmerregelen: kopiering og flytting
    // ================================================
    seksjon("2.6 Kopikonstruktør");
    IncidenceGraph ig3;
    ig3.insert_edge("X", "kant", "Y");
    IncidenceGraph ig4 = ig3;           // kopikonstruktør
    ig3.insert_edge("Y", "kant2", "Z"); // endre original
    std::cout << "Original (endret):\n";
    ig3.write(std::cout);
    std::cout << "Kopi (uendret):\n";
    ig4.write(std::cout);               // skal ikke ha kant2 – dyp kopi

    seksjon("2.6 Kopitildelingsoperator");
    IncidenceGraph ig5;
    ig5.insert_edge("P", "kant", "Q");
    ig5 = ig3;                          // kopitildelingsoperator
    std::cout << "Etter tildelning fra ig3:\n";
    ig5.write(std::cout);

    seksjon("2.6 Flyttekonstruktør");
    IncidenceGraph ig6 = std::move(ig4); // flyttekonstruktør
    std::cout << "ig6 etter move fra ig4:\n";
    ig6.write(std::cout);
    std::cout << "ig4 etter move (skal være tom):\n";
    ig4.write(std::cout);

    seksjon("2.6 Flyttetildelingsoperator");
    IncidenceGraph ig7;
    ig7 = std::move(ig6);               // flyttetildelingsoperator
    std::cout << "ig7 etter move fra ig6:\n";
    ig7.write(std::cout);

    std::cout << "\nAlle tester fullført.\n";
    return 0;
}