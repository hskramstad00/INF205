#pragma once
#include "graph.h"

#include <list>
#include <memory>
#include <string>
#include <unordered_map>

class IncidenceGraph : public Graph {
private:
    struct Edge;

    struct Node {
        explicit Node(std::string lbl) : label(std::move(lbl)) {}
        std::string label;
        std::list<Edge*> out; // utgående kanter
        std::list<Edge*> in;  // inngående kanter
    };

    struct Edge {
        Edge(std::string lbl, Node* f, Node* t)
            : label(std::move(lbl)), from(f), to(t) {}
        std::string label;
        Node* from;
        Node* to;
    };

    std::list<std::unique_ptr<Node>> nodes_;
    std::list<std::unique_ptr<Edge>> edges_;

    // Raskt oppslag: label -> Node*
    std::unordered_map<std::string, Node*> by_label_;

    Node* find_node_(const std::string& label) const;
    Node* get_or_create_node_(const std::string& label);

    void remove_edge_(Edge* e);
    void cleanup_isolated_nodes_();

public:
    // Rule of five
    IncidenceGraph() = default;
    ~IncidenceGraph() override = default;

    IncidenceGraph(const IncidenceGraph& other);            
    IncidenceGraph& operator=(const IncidenceGraph& other); 

    IncidenceGraph(IncidenceGraph&&) noexcept = default;
    IncidenceGraph& operator=(IncidenceGraph&&) noexcept = default;

    void insert_edge(std::string a, std::string edge_label, std::string b) override;
    void disconnect(std::string a, std::string b) override;
    void remove_node(std::string label) override;
    void write(std::ostream& os) const override;
    void read(std::istream& is) override;
    void clear() override;
};