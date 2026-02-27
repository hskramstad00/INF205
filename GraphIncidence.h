#pragma once

#include "Graph.h"

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>  // std::swap

class GraphIncidence final : public Graph {
private:
    struct Edge;

    struct Node {
        explicit Node(std::string lbl) : label(std::move(lbl)) {}
        std::string label;

        // Insidenslister:
        std::list<Edge*> out; // kanter som går ut fra denne noden
        std::list<Edge*> in;  // kanter som går inn til denne noden
    };

    struct Edge {
        Edge(std::string lbl, Node* f, Node* t)
            : label(std::move(lbl)), from(f), to(t) {}
        std::string label; // ikke-unik
        Node* from;
        Node* to;
    };

    // Eierskap: grafen eier alle noder og kanter
    std::list<std::unique_ptr<Node>> nodes_;
    std::list<std::unique_ptr<Edge>> edges_;

    // Raskt oppslag for node-label -> Node*
    std::unordered_map<std::string, Node*> by_label_;

    Node* get_or_create_node_(const std::string& label);
    Node* find_node_(const std::string& label) const;

    void cleanup_isolated_nodes_();
    void remove_edge_(Edge* e);

public:
    // --- Rule of Five ---
    GraphIncidence() = default;
    ~GraphIncidence() override = default;

    GraphIncidence(const GraphIncidence& other);             // deep copy
    GraphIncidence& operator=(const GraphIncidence& other);  // deep copy

    GraphIncidence(GraphIncidence&& other) noexcept = default;
    GraphIncidence& operator=(GraphIncidence&& other) noexcept = default;

    friend void swap(GraphIncidence& a, GraphIncidence& b) noexcept;

    // --- Graph API ---
    void insert_edge(const std::string& node_a_label,
                     const std::string& edge_label,
                     const std::string& node_b_label) override;

    void disconnect(const std::string& node_a_label,
                    const std::string& node_b_label) override;

    void remove_node(const std::string& node_label) override;

    void read_from_file(const std::string& path) override;
    void write_to_file(const std::string& path) const override;
};