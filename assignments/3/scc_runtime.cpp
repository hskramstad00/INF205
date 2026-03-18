#include "graph.h"
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include "scc.h"

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Clock = std::chrono::high_resolution_clock;

std::unique_ptr<Graph> make_graph(const std::string& mode) {
    if (mode == "matrix") return std::make_unique<MatrixGraph>();
    return std::make_unique<IncidenceGraph>();
}

bool load_graph(Graph& g, const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;
    g.clear();
    g.read(in);
    return true;
}

double time_one_run_ms(const Graph& g) {
    auto t0 = Clock::now();
    auto sccs = tarjan_scc(g, false);
    auto t1 = Clock::now();
    (void)sccs;
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

bool generate_graph(long n, long e, const std::string& graph_file) {
    std::ostringstream cmd;
    cmd << "./graph-benchmark-scc " << n << ' ' << e << ' ' << graph_file << " > /dev/null";
    return std::system(cmd.str().c_str()) == 0;
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 7) {
        std::cerr << "Usage: " << argv[0]
                  << " <n_start> <n_end> <factor> <edge_multiplier> <repeats> <csv_out>\n"
                  << "Example: " << argv[0] << " 128 4096 2 8 5 scc_results.csv\n";
        return 1;
    }

    const long n_start = std::stol(argv[1]);
    const long n_end = std::stol(argv[2]);
    const long factor = std::stol(argv[3]);
    const long edge_multiplier = std::stol(argv[4]);
    const int repeats = std::stoi(argv[5]);
    const std::string csv_out = argv[6];

    if (n_start <= 0 || n_end < n_start || factor < 2 || edge_multiplier <= 0 || repeats <= 0) {
        std::cerr << "Invalid arguments.\n";
        return 1;
    }

    std::ofstream csv(csv_out);
    if (!csv) {
        std::cerr << "Cannot open output file: " << csv_out << "\n";
        return 1;
    }

    csv << "n,edges,representation,repeat,time_ms\n";
    std::cout << std::fixed << std::setprecision(3);

    for (long n = n_start; n <= n_end; n *= factor) {
        const long edges = std::max(n, edge_multiplier * n);
        const std::string graph_file = "bench_scc_" + std::to_string(n) + ".dat";

        std::cout << "Generating SCC graph for n=" << n << ", e=" << edges << " ...\n";
        if (!generate_graph(n, edges, graph_file)) {
            std::cerr << "Generator failed for n=" << n << "\n";
            return 1;
        }

        for (const std::string mode : {std::string("incidence"), std::string("matrix")}) {
            auto g = make_graph(mode);
            if (!load_graph(*g, graph_file)) {
                std::cerr << "Could not load graph file: " << graph_file << "\n";
                return 1;
            }

            double sum = 0.0;
            for (int r = 1; r <= repeats; ++r) {
                double ms = time_one_run_ms(*g);
                sum += ms;
                csv << n << ',' << edges << ',' << mode << ',' << r << ',' << ms << '\n';
            }
            std::cout << "  " << mode << ": avg " << (sum / repeats) << " ms\n";
        }
    }

    std::cout << "\nSaved raw measurements to " << csv_out << "\n";
    return 0;
}