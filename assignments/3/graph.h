#pragma once
#include <string>
#include <vector>
#include <iosfwd>
#include <utility>   // std::pair

class Graph {
public:
    virtual ~Graph() = default;

    virtual void insert_edge(std::string node_a_label,
                             std::string edge_label,
                             std::string node_b_label) = 0;

    virtual void disconnect(std::string node_a_label,
                            std::string node_b_label) = 0;

    virtual void remove_node(std::string node) = 0;

    virtual void write(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual void clear() = 0;


    /// Returns labels of every node currently in the graph.
    virtual std::vector<std::string> nodes() const = 0;

    /// Returns all outgoing edges of @p node as {edge_label, target_node} pairs.
    virtual std::vector<std::pair<std::string,std::string>>
    out_edges(const std::string& node) const = 0;

    /// Returns labels of all successor nodes reachable from @p node via an
    /// edge whose label equals @p edge_label.
    virtual std::vector<std::string>
    successors(const std::string& node,
               const std::string& edge_label) const = 0;
};
