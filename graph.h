#pragma once
#include <string>
#include <vector>
#include <iosfwd>

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

        virtual std::vector<std::string> get_nodes() const = 0;

        virtual std::vector<std::string> get_neighbors(const std::string& from) const = 0;

        virtual std::vector<std::string> get_neighbors_with_label(
            const std::string& from,
            const std::string& edge_label) const = 0;
};