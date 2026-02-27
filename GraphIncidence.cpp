#include "GraphIncidence.h"

#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <utility>   // std::swap

// -------------------- private helpers --------------------

GraphIncidence::Node* GraphIncidence::find_node_(const std::string& label) const {
    auto it = by_label_.find(label);
    return (it == by_label_.end()) ? nullptr : it->second;
}

GraphIncidence::Node* GraphIncidence::get_or_create_node_(const std::string& label) {
    if (auto* n = find_node_(label)) return n;

    nodes_.push_back(std::make_unique<Node>(label));
    Node* raw = nodes_.back().get();
    by_label_[label] = raw;
    return raw;
}

// -------------------- Graph API --------------------

void GraphIncidence::insert_edge(const std::string& node_a_label,
                                 const std::string& edge_label,
                                 const std::string& node_b_label) {
    Node* a = get_or_create_node_(node_a_label);
    Node* b = get_or_create_node_(node_b_label);

    edges_.push_back(std::make_unique<Edge>(edge_label, a, b));
    Edge* e = edges_.back().get();

    a->out.push_back(e);
    b->in.push_back(e);
}

void GraphIncidence::read_from_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Could not open file for reading: " + path);

    std::string a, el, b;
    while (in >> a >> el >> b) {
        insert_edge(a, el, b);
    }
}

void GraphIncidence::write_to_file(const std::string& path) const {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Could not open file for writing: " + path);

    for (const auto& ep : edges_) {
        out << ep->from->label << " " << ep->label << " " << ep->to->label << "\n";
    }
}

// -------------------- 2.5: delete edges/nodes --------------------

void GraphIncidence::disconnect(const std::string& node_a_label,
                                const std::string& node_b_label) {
    Node* a = find_node_(node_a_label);
    Node* b = find_node_(node_b_label);
    if (!a || !b) return;

    // Gå gjennom alle utkanter fra a, og fjern de som går til b
    auto it = a->out.begin();
    while (it != a->out.end()) {
        Edge* e = *it;
        ++it; // advance før slett (iteratoren vi sto på kan bli invalid)
        if (e->to == b) {
            remove_edge_(e);
        }
    }

    cleanup_isolated_nodes_();
}

void GraphIncidence::remove_node(const std::string& node_label) {
    Node* n = find_node_(node_label);
    if (!n) return;

    // Fjern alle utkanter (sletter samtidig fra andre noders in-lister)
    while (!n->out.empty()) {
        Edge* e = n->out.front();
        remove_edge_(e);
    }

    // Fjern alle innkanter (sletter samtidig fra andre noders out-lister)
    while (!n->in.empty()) {
        Edge* e = n->in.front();
        remove_edge_(e);
    }

    // Fjern noden fra map
    by_label_.erase(n->label);

    // Fjern noden fra container (unique_ptr)
    for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
        if (it->get() == n) {
            nodes_.erase(it);
            break;
        }
    }

    cleanup_isolated_nodes_();
}

void GraphIncidence::remove_edge_(Edge* e) {
    if (!e) return;

    Node* from = e->from;
    Node* to   = e->to;

    // Fjern edge-peker fra from->out
    if (from) {
        for (auto it = from->out.begin(); it != from->out.end(); ++it) {
            if (*it == e) {
                from->out.erase(it);
                break;
            }
        }
    }

    // Fjern edge-peker fra to->in
    if (to) {
        for (auto it = to->in.begin(); it != to->in.end(); ++it) {
            if (*it == e) {
                to->in.erase(it);
                break;
            }
        }
    }

    // Fjern selve Edge-objektet fra edges_ (unique_ptr)
    for (auto it = edges_.begin(); it != edges_.end(); ++it) {
        if (it->get() == e) {
            edges_.erase(it);
            break;
        }
    }
}

void GraphIncidence::cleanup_isolated_nodes_() {
    // Slett alle noder som ikke har inn- eller utkanter
    auto it = nodes_.begin();
    while (it != nodes_.end()) {
        Node* n = it->get();
        if (n->in.empty() && n->out.empty()) {
            by_label_.erase(n->label);
            it = nodes_.erase(it);
        } else {
            ++it;
        }
    }
}

// -------------------- 2.6: Rule of Five (deep copy for incidence) --------------------

void swap(GraphIncidence& a, GraphIncidence& b) noexcept {
    using std::swap;
    swap(a.nodes_, b.nodes_);
    swap(a.edges_, b.edges_);
    swap(a.by_label_, b.by_label_);
}

// Copy constructor: deep copy (noder + kanter + insidenslister)
GraphIncidence::GraphIncidence(const GraphIncidence& other) {
    // Map fra gamle Node* til nye Node*
    std::unordered_map<const Node*, Node*> old2new;
    old2new.reserve(other.nodes_.size());

    // 1) Kopier noder
    for (const auto& np : other.nodes_) {
        nodes_.push_back(std::make_unique<Node>(np->label));
        Node* new_node = nodes_.back().get();
        by_label_[new_node->label] = new_node;
        old2new[np.get()] = new_node;
    }

    // 2) Kopier kanter og bygg insidenslistene på nytt
    for (const auto& ep : other.edges_) {
        Node* new_from = old2new.at(ep->from);
        Node* new_to   = old2new.at(ep->to);

        edges_.push_back(std::make_unique<Edge>(ep->label, new_from, new_to));
        Edge* new_edge = edges_.back().get();

        new_from->out.push_back(new_edge);
        new_to->in.push_back(new_edge);
    }
}

// Copy assignment: copy-and-swap (sterk unntaksgaranti)
GraphIncidence& GraphIncidence::operator=(const GraphIncidence& other) {
    if (this == &other) return *this;
    GraphIncidence tmp(other);
    swap(*this, tmp);
    return *this;
}

// Move ctor/assignment og destruktør kan være default (eies av containers/unique_ptr)
// (De må være deklarert i headeren.)