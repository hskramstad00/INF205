#include "graph.h"
#include <vector>
#include <list>
#include <string>

class MatrixGraph : public Graph {
    public:
        MatrixGraph() = default;
        MatrixGraph(const MatrixGraph&) = default;
        MatrixGraph(MatrixGraph&&) noexcept = default;
        MatrixGraph& operator=(const MatrixGraph&) = default;
        MatrixGraph& operator=(MatrixGraph&&) noexcept = default;
        ~MatrixGraph() = default;


        void insert_edge(std::string a, std::string edge_label, std::string b) override;
        void disconnect(std::string a, std::string b) override;
        void remove_node(std::string label) override;
        void write(std::ostream& os) const override;
        void read(std::istream& is) override;

    private:
        std::vector<std::string> node_labels;
        // adjacency[i][j] = liste over kantetiketter fra node i til node j
        std::vector<std::vector<std::list<std::string>>> adjacency;

        int find_or_create_node(const std::string& label);
        int find_node(const std::string& label) const; // returnerer -1 om ikke funnet
        void resize_matrix(int new_size);
        void remove_isolated_nodes();
};