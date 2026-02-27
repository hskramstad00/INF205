#include <string>

class Graph {
    public:
        void virtual insert_edge(std::string node_a_label,std::string edge_label, std::string node_b_labe);

        void virtual disconnect(std::string node_a_label, std::string node_b_label);

        void virtual remove_node(std::string node);

        void virtual write(std::ostream& os) const = 0;

        void virtual read(std::istream& is) = 0;

        void virtual clear() = 0;
};