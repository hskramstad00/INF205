#pragma once
#include <string>

class Graph {
public:
    virtual ~Graph() = default;

    virtual void insert_edge(const std::string& node_a_label,
                             const std::string& edge_label,
                             const std::string& node_b_label) = 0;

    // Slett alle kanter fra a -> b (kun den retningen).
    virtual void disconnect(const std::string& node_a_label,
                            const std::string& node_b_label) = 0;

    // Slett node + alle kanter som er incident til den.
    virtual void remove_node(const std::string& node_label) = 0;

    // Filformat: "node_a_label edge_label node_b_label" per linje
    virtual void read_from_file(const std::string& path) = 0;
    virtual void write_to_file(const std::string& path) const = 0;
};