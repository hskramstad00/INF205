#include "graph.h"
#include "incidenceListGraph.h"
#include "adjacencyMatrixGraph.h"
#include "diamond.h"

#include <chrono>
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

bool load_query(const std::string& filename,
                std::vector<std::string>& path1,
                std::vector<std::string>& path2) {
    std::ifstream in(filename);
    if (!in) return false;
    read_query(in, path1, path2);
    return true;
}

double time_one_run_ms(const Graph& g,
                       const std::vector<std::string>& path1,
                       const std::vector<std::string>& path2) {
    auto t0 = Clock::now();
    auto pairs = diamond_query(g, path1, path2, false);
    auto t1 = Clock::now();
    (void)pairs;
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

bool generate_graph(long n, int m,
                    const std::string& graph_file,
                    const std::string& query_file) {
    std::ostringstream cmd;
    cmd << "./generate-graph " << n << ' ' << m << ' ' << graph_file << ' ' << query_file << " > /dev/null";
    return std::system(cmd.str().c_str()) == 0;
}

} 

int main(int argc, char** argv) {
    if (argc != 8) {
        std::cerr << "Usage: " << argv[0]
                  << " <n_start> <n_end> <factor> <constant_m> <proportional_divisor> <repeats> <csv_out>\n"
                  << "Example: " << argv[0] << " 128 4096 2 4 16 5 diamond_results.csv\n"
                  << "This runs two scenarios:\n"
                  << "  constant:     m = constant_m\n"
                  << "  proportional: m = max(1, n / proportional_divisor)\n";
        return 1;
    }

    const long n_start = std::stol(argv[1]);
    const long n_end = std::stol(argv[2]);
    const long factor = std::stol(argv[3]);
    const int constant_m = std::stoi(argv[4]);
    const long proportional_divisor = std::stol(argv[5]);
    const int repeats = std::stoi(argv[6]);
    const std::string csv_out = argv[7];

    if (n_start <= 0 || n_end < n_start || factor < 2 || constant_m <= 0 || proportional_divisor <= 0 || repeats <= 0) {
        std::cerr << "Invalid arguments.\n";
        return 1;
    }

    std::ofstream csv(csv_out);
    if (!csv) {
        std::cerr << "Cannot open output file: " << csv_out << "\n";
        return 1;
    }

    csv << "scenario,n,m,representation,repeat,time_ms\n";
    std::cout << std::fixed << std::setprecision(3);

    for (long n = n_start; n <= n_end; n *= factor) {
        for (const std::string& scenario : {std::string("constant"), std::string("proportional")}) {
            const int m = (scenario == "constant") ? constant_m : std::max(1L, n / proportional_divisor);
            const std::string graph_file = "bench_diamond_" + scenario + "_" + std::to_string(n) + ".dat";
            const std::string query_file = "bench_diamond_" + scenario + "_" + std::to_string(n) + ".qry";

            std::cout << "Generating diamond graph for scenario=" << scenario
                      << ", n=" << n << ", m=" << m << " ...\n";
            if (!generate_graph(n, m, graph_file, query_file)) {
                std::cerr << "Generator failed for n=" << n << ", m=" << m << "\n";
                return 1;
            }

            std::vector<std::string> path1, path2;
            if (!load_query(query_file, path1, path2)) {
                std::cerr << "Could not load query file: " << query_file << "\n";
                return 1;
            }

            for (const std::string& mode : {std::string("incidence"), std::string("matrix")}) {
                auto g = make_graph(mode);
                if (!load_graph(*g, graph_file)) {
                    std::cerr << "Could not load graph file: " << graph_file << "\n";
                    return 1;
                }

                double sum = 0.0;
                for (int r = 1; r <= repeats; ++r) {
                    double ms = time_one_run_ms(*g, path1, path2);
                    sum += ms;
                    csv << scenario << ',' << n << ',' << m << ',' << mode << ',' << r << ',' << ms << '\n';
                }
                std::cout << "  " << mode << ": avg " << (sum / repeats) << " ms\n";
            }
        }
    }

    std::cout << "\nSaved raw measurements to " << csv_out << "\n";
    return 0;
}