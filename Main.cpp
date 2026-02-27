#include "GraphIncidence.h"
#include "GraphMatrix.h"

#include <iostream>
#include <memory>
#include <string>

static void usage(const char* prog) {
    std::cout
        << "Usage:\n"
        << "  " << prog << " <matrix|incidence> <input.txt> <output.txt>\n"
        << "Optional operations:\n"
        << "  " << prog << " <matrix|incidence> <input.txt> <output.txt> disconnect <A> <B>\n"
        << "  " << prog << " <matrix|incidence> <input.txt> <output.txt> remove_node <X>\n";
}

int main(int argc, char** argv) {
    if (argc < 4) {
        usage(argv[0]);
        return 1;
    }

    const std::string impl = argv[1];
    const std::string in_path = argv[2];
    const std::string out_path = argv[3];

    try {
        std::unique_ptr<Graph> g;

        if (impl == "matrix") {
            g = std::make_unique<GraphMatrix>();
        } else if (impl == "incidence") {
            g = std::make_unique<GraphIncidence>();
        } else {
            std::cerr << "Unknown implementation: " << impl << "\n";
            usage(argv[0]);
            return 1;
        }

        // Les inn graf fra fil
        g->read_from_file(in_path);

        // Eventuelle ekstra operasjoner
        if (argc >= 5) {
            const std::string op = argv[4];

            if (op == "disconnect") {
                if (argc != 7) {
                    std::cerr << "disconnect requires 2 node labels\n";
                    usage(argv[0]);
                    return 1;
                }
                g->disconnect(argv[5], argv[6]);
            } else if (op == "remove_node") {
                if (argc != 6) {
                    std::cerr << "remove_node requires 1 node label\n";
                    usage(argv[0]);
                    return 1;
                }
                g->remove_node(argv[5]);
            } else {
                std::cerr << "Unknown operation: " << op << "\n";
                usage(argv[0]);
                return 1;
            }
        }

        // Skriv graf til fil
        g->write_to_file(out_path);

        std::cout << "OK: wrote " << out_path << "\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}