#include "graph.h"
#include <string>
#include <list>

class incidenceGraph : public Graph {
    public:
        incidenceGraph() = default;
        incidenceGraph(const incidenceGraph& other);
        incidenceGraph(incidenceGraph&& other) noexcept;
        incidenceGraph& operator=(const incidenceGraph& other);
        incidenceGraph& operator=(incidenceGraph&& other) noexcept;
        ~incidenceGraph();

        void insert_edge(std::string a, std::string edge_label, std::string b) override;
        void disconnect(std::string a, std::string b) override;
        void remove_node(std::string label) override;
        void read(std::istream& os) override;
        void write(std::ostream& iss) const override;

    private:

        struct Node;

        struct Edge {
            std::string label;
            Node* from;
            Node* to;
        };

        struct Node {
            std::string label;
            std::list<Edge*> incident_edges;
        };
        
        std::list<Node*> nodes;
        std::list<Edge*> edges;

        Node* find_or_create_node(const std::string& label);
        Node* find_node(const std::string& label) const;
        void remove_isolated_nodes();


};