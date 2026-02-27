#pragma once
#include "Graph.h"

#include <string>
#include <unordered_map>
#include <vector>

class GraphMatrix final : public Graph {
private:
    // labels_[i] er label for node i
    std::vector<std::string> labels_;
    std::unordered_map<std::string, std::size_t> index_;

    // adj_[i][j] = liste av edge-labels for kanter i -> j (multikanter)
    std::vector<std::vector<std::vector<std::string>>> adj_;

    std::size_t get_or_add_index_(const std::string& label);
    std::size_t find_index_(const std::string& label) const;
    void cleanup_isolated_nodes_(); // TODO (2.5)
    void remove_index_(std::size_t idx); // TODO (2.5): fjerne rad/kolonne

public:
    GraphMatrix() = default;

    void insert_edge(const std::string& node_a_label,
                     const std::string& edge_label,
                     const std::string& node_b_label) override;

    void disconnect(const std::string& node_a_label,
                    const std::string& node_b_label) override;

    void remove_node(const std::string& node_label) override;

    void read_from_file(const std::string& path) override;
    void write_to_file(const std::string& path) const override;
};