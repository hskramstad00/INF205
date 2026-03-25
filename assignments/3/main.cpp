#include "graph.h"
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include <fstream>
#include <iostream>

// Hjelpe funksjon for printing
void seksjon(const std::string& tittel) {
    std::cout << "\n========== " << tittel << " ==========\n";
}

int main(int argc, char* argv[]) {
    std::string oppgave = (argc > 1) ? argv[1] : "all";

    if (oppgave == "22" || oppgave == "all"){
        // Oppgave 2.2 - FIl input/ skriv til fil
        seksjon("2.2 Fil I/O: skriv til fil");

        // må først insert edge for å få opprettet nodene
        IncidenceGraph ig;
        ig.insert_edge("Oslo",      "fly",  "Bergen");
        ig.insert_edge("Bergen",    "tog",  "Trondheim");
        ig.insert_edge("Oslo",      "bil",  "Trondheim");
        ig.insert_edge("Oslo",      "fly",  "Oslo");  
        ig.insert_edge("Oslo",      "buss", "Bergen"); 
        ig.write(std::cout);

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
    }


    // Oppgave 2.3 - Abstrakt klasse
    if (oppgave == "23" || oppgave == "all"){
        seksjon("2.3 Abstrakt grensesnitt via Graph*");
        Graph* abstrakt = new IncidenceGraph();
        abstrakt->insert_edge("A", "kant1", "B");
        abstrakt->insert_edge("B", "kant2", "C");
        abstrakt->write(std::cout);
        delete abstrakt;
    }

    // Oppgave 2.4 - Matrisebasert graf
    if (oppgave == "24" || oppgave == "all"){
        seksjon("2.4 MatrixGraph: insert_edge");
        MatrixGraph mg;
        mg.insert_edge("Oslo",   "fly",  "Bergen");
        mg.insert_edge("Bergen", "tog",  "Trondheim");
        mg.insert_edge("Oslo",   "buss", "Bergen");   
        mg.insert_edge("Oslo",   "fly",  "Oslo");    
        mg.write(std::cout);
    }

    // Oppgave 2.5 - slette kanter og noder
    if (oppgave == "25" || oppgave == "all"){
        MatrixGraph mg;
        mg.insert_edge("Oslo",   "fly",  "Bergen");
        mg.insert_edge("Bergen", "tog",  "Trondheim");
        mg.insert_edge("Oslo",   "buss", "Bergen");   
        mg.insert_edge("Oslo",   "fly",  "Oslo");    
        seksjon("2.5 disconnect: fjern alle kanter Oslo->Bergen");
        mg.disconnect("Oslo", "Bergen");
        mg.write(std::cout);


        seksjon("2.5 remove_node: fjern Bergen");
        IncidenceGraph ig2;
        ig2.insert_edge("Oslo",      "fly",  "Bergen");
        ig2.insert_edge("Bergen",    "tog",  "Trondheim");
        ig2.insert_edge("Stavanger", "buss", "Oslo");
        std::cout << "Før remove_node:\n";
        ig2.write(std::cout);
        ig2.remove_node("Bergen");
        std::cout << "Etter remove_node(Bergen) - isolerte noder skal også forsvinne:\n";
        ig2.write(std::cout);
    }

    // Oppgave 2.6 - femmerreglen - kopiering og flytting
    if (oppgave == "26" || oppgave == "all"){
        seksjon("2.6 Kopikonstruktør");
        IncidenceGraph ig3;
        ig3.insert_edge("X", "kant", "Y");
        IncidenceGraph ig4 = ig3;           
        ig3.insert_edge("Y", "kant2", "Z"); 
        std::cout << "Original (endret):\n";
        ig3.write(std::cout);
        std::cout << "Kopi (uendret):\n";
        ig4.write(std::cout);               

        seksjon("2.6 Kopitildelingsoperator");
        IncidenceGraph ig5;
        ig5.insert_edge("P", "kant", "Q");
        ig5 = ig3;                          
        std::cout << "Etter tildelning fra ig3:\n";
        ig5.write(std::cout);

        seksjon("2.6 Flyttekonstruktør");
        IncidenceGraph ig6 = std::move(ig4); 
        std::cout << "ig6 etter move fra ig4:\n";
        ig6.write(std::cout);
        std::cout << "ig4 etter move (skal være tom):\n";
        ig4.write(std::cout);

        seksjon("2.6 Flyttetildelingsoperator");
        IncidenceGraph ig7;
        ig7 = std::move(ig6);             
        std::cout << "ig7 etter move fra ig6:\n";
        ig7.write(std::cout);
    }

    
    return 0;
}