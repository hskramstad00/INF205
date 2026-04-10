#pragma once
#include <string>
#include <vector>
#include <iosfwd>
#include <utility>

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

    // vector of all nodes
    virtual std::vector<std::string> nodes() const = 0;
    
    // returns node labels and edges labels which a give node can reach with one edge
    virtual std::vector<std::pair<std::string,std::string>>
    out_edges(const std::string& node) const = 0;
    
    // returns node label for all outgoing edges from a give node with given edge label
    virtual std::vector<std::string>
    successors(const std::string& node,
               const std::string& edge_label) const = 0;
};
