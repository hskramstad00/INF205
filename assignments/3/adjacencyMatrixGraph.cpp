#include "adjacencyMatrixGraph.h"
#include <iostream>

// loop through node labels to find index of given label, or -1 if not found
int MatrixGraph::find_node_(const std::string& label) const {
    for (int i = 0; i < (int)node_labels_.size(); ++i)
        if (node_labels_[i] == label) return i;
    return -1;
}

// find index of given label, or create new node if not found and return new index
int MatrixGraph::find_or_create_node_(const std::string& label) {
    int i = find_node_(label);
    if (i != -1) return i;
    node_labels_.push_back(label);
    int n = (int)node_labels_.size();
    for (auto& row : adjacency_) row.emplace_back();     
    adjacency_.emplace_back(n);                          
    return n - 1;
}

// remove all nodes with no incoming or outgoing edges found
void MatrixGraph::remove_isolated_nodes_() {
    bool found = true;
    while (found) {
        found = false;
        for (int i = 0; i < (int)node_labels_.size(); ++i) {
            bool isolated = true;
            for (int j = 0; j < (int)node_labels_.size() && isolated; ++j)
                if (!adjacency_[i][j].empty() || !adjacency_[j][i].empty())
                    isolated = false;
            if (isolated) {
                adjacency_.erase(adjacency_.begin() + i);
                for (auto& row : adjacency_) row.erase(row.begin() + i);
                node_labels_.erase(node_labels_.begin() + i);
                found = true;
                break;
            }
        }
    }
}

// Oppgave 2

void MatrixGraph::insert_edge(std::string a, std::string edge_label, std::string b) {
    int i = find_or_create_node_(a);
    int j = find_or_create_node_(b);
    adjacency_[i][j].push_back(edge_label);
}

void MatrixGraph::disconnect(std::string a, std::string b) {
    int i = find_node_(a);
    int j = find_node_(b);
    if (i == -1 || j == -1) return;
    adjacency_[i][j].clear();
    remove_isolated_nodes_();
}

void MatrixGraph::remove_node(std::string label) {
    int i = find_node_(label);
    if (i == -1) return;
    adjacency_.erase(adjacency_.begin() + i);
    for (auto& row : adjacency_) row.erase(row.begin() + i);
    node_labels_.erase(node_labels_.begin() + i);
    remove_isolated_nodes_();
}

void MatrixGraph::write(std::ostream& os) const {
    int n = (int)node_labels_.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (const auto& lbl : adjacency_[i][j])
                os << node_labels_[i] << " " << lbl << " " << node_labels_[j] << ".\n";
}

void MatrixGraph::read(std::istream& is) {
    std::string a, el, b;
    while (is >> a >> el >> b) {
        if (!b.empty() && b.back() == '.') b.pop_back();
        insert_edge(a, el, b);
    }
}

void MatrixGraph::clear() {
    node_labels_.clear();
    adjacency_.clear();
}

// Oppgave 3

std::vector<std::string> MatrixGraph::nodes() const {
    return node_labels_;
}

std::vector<std::pair<std::string,std::string>>
MatrixGraph::out_edges(const std::string& node) const {
    std::vector<std::pair<std::string,std::string>> result;
    int i = find_node_(node);
    if (i == -1) return result;
    int n = (int)node_labels_.size();
    for (int j = 0; j < n; ++j)
        for (const auto& lbl : adjacency_[i][j])
            result.emplace_back(lbl, node_labels_[j]);
    return result;
}

std::vector<std::string>
MatrixGraph::successors(const std::string& node,
                         const std::string& edge_label) const {
    std::vector<std::string> result;
    int i = find_node_(node);
    if (i == -1) return result;
    int n = (int)node_labels_.size();
    for (int j = 0; j < n; ++j)
        for (const auto& lbl : adjacency_[i][j])
            if (lbl == edge_label) result.push_back(node_labels_[j]);
    return result;
}
