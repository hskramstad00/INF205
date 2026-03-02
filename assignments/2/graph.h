#pragma once
#include <string>
#include <iosfwd>

class Graph {
    public:

        virtual ~Graph() = default;
        
        void virtual insert_edge(std::string node_a_label,std::string edge_label, std::string node_b_label) = 0;

        void virtual disconnect(std::string node_a_label, std::string node_b_label) = 0;

        void virtual remove_node(std::string node) = 0;

        void virtual write(std::ostream& os) const = 0;

        void virtual read(std::istream& is) = 0;

        void virtual clear() = 0;
};