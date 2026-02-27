#include "incidenceListGraph.h"
#include <iostream>
#include <stdexcept>

// ---------- Private hjelpemetoder ----------

IncidenceGraph::Node* IncidenceGraph::find_node(const std::string& label) const {
    for(Node* n : nodes)
        if(n->label == label) return n;
    return nullptr;
}

IncidenceGraph::Node* IncidenceGraph::find_or_create_node(const std::string& label) {
    Node* n = find_node(label);
    if(n == nullptr) {
        n = new Node{label, {}};
        nodes.push_back(n);
    }
    return n;
}

void IncidenceGraph::remove_isolated_nodes() {
    // Fjern noder som ikke har noen insidente kanter
    auto it = nodes.begin();
    while(it != nodes.end()) {
        if((*it)->incident_edges.empty()) {
            delete *it;
            it = nodes.erase(it);
        } else {
            ++it;
        }
    }
}

// ---------- insert_edge ----------

void IncidenceGraph::insert_edge(std::string a, std::string edge_label, std::string b) {
    Node* node_a = find_or_create_node(a);
    Node* node_b = find_or_create_node(b);

    Edge* e = new Edge{edge_label, node_a, node_b};
    edges.push_back(e);
    node_a->incident_edges.push_back(e);
    node_b->incident_edges.push_back(e);
}

// ---------- disconnect ----------

void IncidenceGraph::disconnect(std::string a, std::string b) {
    Node* node_a = find_node(a);
    Node* node_b = find_node(b);
    if(node_a == nullptr || node_b == nullptr) return;

    // Finn alle kanter fra a til b og slett dem
    auto it = edges.begin();
    while(it != edges.end()) {
        Edge* e = *it;
        if(e->from == node_a && e->to == node_b) {
            // Fjern fra insidenslista til begge noder
            node_a->incident_edges.remove(e);
            node_b->incident_edges.remove(e);
            delete e;
            it = edges.erase(it);
        } else {
            ++it;
        }
    }
    remove_isolated_nodes();
}

// ---------- remove_node ----------

void IncidenceGraph::remove_node(std::string label) {
    Node* node = find_node(label);
    if(node == nullptr) return;

    // Slett alle kanter som involverer denne noden
    auto it = edges.begin();
    while(it != edges.end()) {
        Edge* e = *it;
        if(e->from == node || e->to == node) {
            // Fjern fra den andre nodens insidensliste
            if(e->from != node) e->from->incident_edges.remove(e);
            if(e->to != node)   e->to->incident_edges.remove(e);
            delete e;
            it = edges.erase(it);
        } else {
            ++it;
        }
    }

    nodes.remove(node);
    delete node;

    remove_isolated_nodes();
}

// ---------- Fil-I/O ----------

void IncidenceGraph::write(std::ostream& os) const {
    for(Edge* e : edges)
        os << e->from->label << " " << e->label << " " << e->to->label << "\n";
}

void IncidenceGraph::read(std::istream& is) {
    std::string a, edge_label, b;
    while(is >> a >> edge_label >> b)
        insert_edge(a, edge_label, b);
}

// ---------- Femmerregelen ----------

IncidenceGraph::~IncidenceGraph() {
    for(Edge* e : edges) delete e;
    for(Node* n : nodes) delete n;
}

IncidenceGraph::IncidenceGraph(const IncidenceGraph& other) {
    // Kopier alle noder først
    for(Node* n : other.nodes)
        nodes.push_back(new Node{n->label, {}});

    // Kopier kanter og koble til riktige (nye) node-objekter
    for(Edge* e : other.edges) {
        Node* new_from = find_node(e->from->label);
        Node* new_to   = find_node(e->to->label);
        Edge* new_edge = new Edge{e->label, new_from, new_to};
        edges.push_back(new_edge);
        new_from->incident_edges.push_back(new_edge);
        new_to->incident_edges.push_back(new_edge);
    }
}

IncidenceGraph::IncidenceGraph(IncidenceGraph&& other) noexcept
    : nodes(std::move(other.nodes)), edges(std::move(other.edges)) {}

IncidenceGraph& IncidenceGraph::operator=(const IncidenceGraph& other) {
    if(this == &other) return *this;
    // Frigjør eget innhold
    for(Edge* e : edges) delete e;
    for(Node* n : nodes) delete n;
    nodes.clear();
    edges.clear();
    // Kopier fra other (samme logikk som kopikonstruktør)
    for(Node* n : other.nodes)
        nodes.push_back(new Node{n->label, {}});
    for(Edge* e : other.edges) {
        Node* new_from = find_node(e->from->label);
        Node* new_to   = find_node(e->to->label);
        Edge* new_edge = new Edge{e->label, new_from, new_to};
        edges.push_back(new_edge);
        new_from->incident_edges.push_back(new_edge);
        new_to->incident_edges.push_back(new_edge);
    }
    return *this;
}

IncidenceGraph& IncidenceGraph::operator=(IncidenceGraph&& other) noexcept {
    if(this == &other) return *this;
    for(Edge* e : edges) delete e;
    for(Node* n : nodes) delete n;
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);
    return *this;
}