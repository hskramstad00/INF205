#pragma once
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
        void clear() override;
        std::vector<std::string> get_nodes() const override;
        std::vector<std::string> get_neighbors(const std::string& from) const override;
        std::vector<std::string> get_neighbors_with_label(
            const std::string& from, const std::string& edge_label) const override;

    private:
        std::vector<std::string> node_labels;
        std::vector<std::vector<std::list<std::string>>> adjacency;

        int find_or_create_node(const std::string& label);
        int find_node(const std::string& label) const;
        void remove_isolated_nodes();
};