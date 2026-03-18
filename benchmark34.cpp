// benchmark34.cpp – Oppgave 3.4: Kjøretidsmåling
//
// Kompiler:
//   g++ -std=c++17 -O2 -o gen-scc graph-benchmark-scc.cpp
//   g++ -std=c++17 -O2 -o gen-diamond graph-benchmark.cpp
//   g++ -std=c++17 -O2 -o benchmark34 benchmark34.cpp scc.cpp diamond.cpp
//       incidenceListGraph.cpp adjacencyMatrixGraph.cpp
//
// Kjør:
//   ./benchmark34 > results.csv

#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include "scc.h"
#include "diamond.h"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Ms    = std::chrono::duration<double, std::milli>;

static void run(const std::string& cmd) {
    if (std::system(cmd.c_str()) != 0) {
        std::cerr << "Feil: " << cmd << "\n";
        std::exit(1);
    }
}

static double time_scc(const std::string& file, bool use_matrix, int reps = 5) {
    double total = 0.0;
    for (int r = 0; r < reps; r++) {
        Graph* g = use_matrix
            ? static_cast<Graph*>(new MatrixGraph())
            : static_cast<Graph*>(new IncidenceGraph());
        std::ifstream inn(file);
        g->read(inn);
        inn.close();

        auto t0 = Clock::now();
        find_sccs(*g);
        auto t1 = Clock::now();

        total += Ms(t1 - t0).count();
        delete g;
    }
    return total / reps;
}

static double time_diamond(const std::string& gfile, const std::string& qfile,
                           bool use_matrix, int reps = 5) {
    std::ifstream qi(qfile);
    DiamondQuery q = read_query(qi);
    qi.close();

    double total = 0.0;
    for (int r = 0; r < reps; r++) {
        Graph* g = use_matrix
            ? static_cast<Graph*>(new MatrixGraph())
            : static_cast<Graph*>(new IncidenceGraph());
        std::ifstream inn(gfile);
        g->read(inn);
        inn.close();

        auto t0 = Clock::now();
        find_diamond_pairs(*g, q);
        auto t1 = Clock::now();

        total += Ms(t1 - t0).count();
        delete g;
    }
    return total / reps;
}

int main() {
    std::vector<int> scc_sizes     = {100, 250, 500, 1000, 2000, 4000};
    std::vector<int> diamond_sizes = {100, 250, 500, 1000, 2000};

    const int QUERY_M_CONST = 5;
    const int REPS = 5;

    // ---- SCC ----
    std::cout << "# SCC timing\n";
    std::cout << "n,incidence_ms,matrix_ms\n";

    for (int n : scc_sizes) {
        int edges = 2 * n;
        std::string gfile = "tmp_scc.txt";
        run("gen-scc " + std::to_string(n) + " " + std::to_string(edges) + " " + gfile);

        double t_inc = time_scc(gfile, false, REPS);
        double t_mat = time_scc(gfile, true,  REPS);

        std::cout << n << "," << t_inc << "," << t_mat << "\n";
        std::cerr << "SCC n=" << n << "  inc=" << t_inc << "ms  mat=" << t_mat << "ms\n";
    }

    // ---- Diamant, konstant m ----
    std::cout << "\n# Diamond timing - konstant m=" << QUERY_M_CONST << "\n";
    std::cout << "n,m,incidence_ms,matrix_ms\n";

    for (int n : diamond_sizes) {
        std::string gfile = "tmp_dia.txt", qfile = "tmp_dia_query.txt";
        run("gen-diamond " + std::to_string(n) + " " + std::to_string(QUERY_M_CONST)
            + " " + gfile + " " + qfile);

        double t_inc = time_diamond(gfile, qfile, false, REPS);
        double t_mat = time_diamond(gfile, qfile, true,  REPS);

        std::cout << n << "," << QUERY_M_CONST << "," << t_inc << "," << t_mat << "\n";
        std::cerr << "Diamond(const m) n=" << n
                  << "  inc=" << t_inc << "ms  mat=" << t_mat << "ms\n";
    }

    // ---- Diamant, m proporsjonal med n ----
    std::cout << "\n# Diamond timing - m proporsjonal med n\n";
    std::cout << "n,m,incidence_ms,matrix_ms\n";

    for (int n : diamond_sizes) {
        int m = std::max(2, (int)std::sqrt((double)n) / 2);
        std::string gfile = "tmp_dia_prop.txt", qfile = "tmp_dia_prop_query.txt";
        run("gen-diamond " + std::to_string(n) + " " + std::to_string(m)
            + " " + gfile + " " + qfile);

        double t_inc = time_diamond(gfile, qfile, false, REPS);
        double t_mat = time_diamond(gfile, qfile, true,  REPS);

        std::cout << n << "," << m << "," << t_inc << "," << t_mat << "\n";
        std::cerr << "Diamond(prop m=" << m << ") n=" << n
                  << "  inc=" << t_inc << "ms  mat=" << t_mat << "ms\n";
    }

    return 0;
}