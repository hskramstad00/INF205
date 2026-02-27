#pragma once
#include "graph.h"
#include <string>
#include <list>

class IncidenceGraph : public Graph {
    public:
        IncidenceGraph() = default;
        IncidenceGraph(const IncidenceGraph& other);
        IncidenceGraph(IncidenceGraph&& other) noexcept;
        IncidenceGraph& operator=(const IncidenceGraph& other);
        IncidenceGraph& operator=(IncidenceGraph&& other) noexcept;
        ~IncidenceGraph();

        void insert_edge(std::string a, std::string edge_label, std::string b) override;
        void disconnect(std::string a, std::string b) override;
        void remove_node(std::string label) override;
        void read(std::istream& os) override;
        void write(std::ostream& iss) const override;
        void clear() override;

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