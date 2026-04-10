#pragma once
#include "graph.h"
#include <vector>
#include <list>
#include <string>
#include <utility>

class MatrixGraph : public Graph {
public:
    // all rule of five defaulted, since we only use STL containers that mange their own memory
    MatrixGraph() = default;
    MatrixGraph(const MatrixGraph&) = default;
    MatrixGraph(MatrixGraph&&) noexcept = default;
    MatrixGraph& operator=(const MatrixGraph&) = default;
    MatrixGraph& operator=(MatrixGraph&&) noexcept = default;
    ~MatrixGraph() = default;

    // Oppgave 2
    void insert_edge(std::string a, std::string edge_label, std::string b) override;
    void disconnect(std::string a, std::string b) override;
    void remove_node(std::string label) override;
    void write(std::ostream& os) const override;
    void read(std::istream& is) override;
    void clear() override;

    // Oppgave 3
    std::vector<std::string> nodes() const override;
    std::vector<std::pair<std::string,std::string>> out_edges(const std::string& node) const override;
    std::vector<std::string> successors(const std::string& node, const std::string& edge_label) const override;

private:
    // all node labels
    std::vector<std::string> node_labels_;

    // the matrix, nodes are columns and rows, each cell contain a list of edge labels
    // row i and column j represent edges from node_labels_[i] to node_labels_[j]
    std::vector<std::vector<std::list<std::string>>> adjacency_;

    // helper functions
    int find_node_(const std::string& label) const;
    int find_or_create_node_(const std::string& label);
    void remove_isolated_nodes_();
};
