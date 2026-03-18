#include "incidenceListGraph.h"
#include <unordered_map>
#include <utility>
#include <istream>
#include <ostream>


IncidenceGraph::Node* IncidenceGraph::find_node_(const std::string& label) const {
    auto it = by_label_.find(label);
    return (it == by_label_.end()) ? nullptr : it->second;
}

IncidenceGraph::Node* IncidenceGraph::get_or_create_node_(const std::string& label) {
    if (auto* n = find_node_(label)) return n;
    nodes_.push_back(std::make_unique<Node>(label));
    Node* raw = nodes_.back().get();
    by_label_[label] = raw;
    return raw;
}

void IncidenceGraph::insert_edge(std::string a, std::string edge_label, std::string b) {
    Node* from = get_or_create_node_(a);
    Node* to   = get_or_create_node_(b);
    edges_.push_back(std::make_unique<Edge>(edge_label, from, to));
    Edge* e = edges_.back().get();
    from->out.push_back(e);
    to->in.push_back(e);
}

void IncidenceGraph::disconnect(std::string a, std::string b) {
    Node* from = find_node_(a);
    Node* to   = find_node_(b);
    if (!from || !to) return;
    auto it = from->out.begin();
    while (it != from->out.end()) {
        Edge* e = *it;
        ++it;
        if (e->to == to) remove_edge_(e);
    }
    cleanup_isolated_nodes_();
}

void IncidenceGraph::remove_node(std::string label) {
    Node* n = find_node_(label);
    if (!n) return;
    while (!n->out.empty()) remove_edge_(n->out.front());
    while (!n->in.empty())  remove_edge_(n->in.front());
    by_label_.erase(n->label);
    for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
        if (it->get() == n) { nodes_.erase(it); break; }
    }
    cleanup_isolated_nodes_();
}

void IncidenceGraph::remove_edge_(Edge* e) {
    e->from->out.remove(e);
    e->to->in.remove(e);
    for (auto it = edges_.begin(); it != edges_.end(); ++it) {
        if (it->get() == e) { edges_.erase(it); break; }
    }
}

void IncidenceGraph::cleanup_isolated_nodes_() {
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

void IncidenceGraph::read(std::istream& is) {
    std::string a, el, b;
    while (is >> a >> el >> b) {
        if (!b.empty() && b.back() == '.') b.pop_back();
        insert_edge(a, el, b);
    }
}

void IncidenceGraph::write(std::ostream& os) const {
    for (const auto& e : edges_)
        os << e->from->label << " " << e->label << " " << e->to->label << "\n";
}

void IncidenceGraph::clear() {
    nodes_.clear();
    edges_.clear();
    by_label_.clear();
}

std::vector<std::string> IncidenceGraph::get_nodes() const {
    std::vector<std::string> result;
    for (const auto& np : nodes_)
        result.push_back(np->label);
    return result;
}

std::vector<std::string> IncidenceGraph::get_neighbors(const std::string& from) const {
    Node* n = find_node_(from);
    if (!n) return {};
    std::vector<std::string> result;
    for (Edge* e : n->out)
        result.push_back(e->to->label);
    return result;
}

std::vector<std::string> IncidenceGraph::get_neighbors_with_label(
    const std::string& from, const std::string& edge_label) const
{
    Node* n = find_node_(from);
    if (!n) return {};
    std::vector<std::string> result;
    for (Edge* e : n->out)
        if (e->label == edge_label)
            result.push_back(e->to->label);
    return result;
}

IncidenceGraph::IncidenceGraph(const IncidenceGraph& other) {
    std::unordered_map<const Node*, Node*> map;
    for (const auto& np : other.nodes_) {
        nodes_.push_back(std::make_unique<Node>(np->label));
        Node* new_node = nodes_.back().get();
        by_label_[new_node->label] = new_node;
        map[np.get()] = new_node;
    }
    for (const auto& ep : other.edges_) {
        Node* from = map.at(ep->from);
        Node* to   = map.at(ep->to);
        edges_.push_back(std::make_unique<Edge>(ep->label, from, to));
        Edge* e = edges_.back().get();
        from->out.push_back(e);
        to->in.push_back(e);
    }
}

IncidenceGraph& IncidenceGraph::operator=(const IncidenceGraph& other) {
    if (this == &other) return *this;
    IncidenceGraph tmp(other);
    std::swap(nodes_, tmp.nodes_);
    std::swap(edges_, tmp.edges_);
    std::swap(by_label_, tmp.by_label_);
    return *this;
}