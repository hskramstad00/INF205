#include "adjacencyMatrixGraph.h"
#include <iostream>
#include <stdexcept>

int MatrixGraph::find_node(const std::string& label) const {
    for (int i = 0; i < (int)node_labels.size(); i++)
        if (node_labels[i] == label) return i;
    return -1;
}

int MatrixGraph::find_or_create_node(const std::string& label) {
    int i = find_node(label);
    if (i != -1) return i;
    node_labels.push_back(label);
    int n = (int)node_labels.size();
    for (auto& row : adjacency)
        row.push_back({});
    adjacency.push_back(std::vector<std::list<std::string>>(n));
    return n - 1;
}

void MatrixGraph::remove_isolated_nodes() {
    bool found = true;
    while (found) {
        found = false;
        for (int i = 0; i < (int)node_labels.size(); i++) {
            bool isolated = true;
            for (int j = 0; j < (int)node_labels.size(); j++)
                if (!adjacency[i][j].empty()) { isolated = false; break; }
            if (isolated)
                for (int j = 0; j < (int)node_labels.size(); j++)
                    if (!adjacency[j][i].empty()) { isolated = false; break; }
            if (isolated) {
                adjacency.erase(adjacency.begin() + i);
                for (auto& row : adjacency)
                    row.erase(row.begin() + i);
                node_labels.erase(node_labels.begin() + i);
                found = true;
                break;
            }
        }
    }
}

void MatrixGraph::insert_edge(std::string a, std::string edge_label, std::string b) {
    int i = find_or_create_node(a);
    int j = find_or_create_node(b);
    adjacency[i][j].push_back(edge_label);
}

void MatrixGraph::disconnect(std::string a, std::string b) {
    int i = find_node(a);
    int j = find_node(b);
    if (i == -1 || j == -1) return;
    adjacency[i][j].clear();
    remove_isolated_nodes();
}

void MatrixGraph::remove_node(std::string label) {
    int i = find_node(label);
    if (i == -1) return;
    adjacency.erase(adjacency.begin() + i);
    for (auto& row : adjacency)
        row.erase(row.begin() + i);
    node_labels.erase(node_labels.begin() + i);
    remove_isolated_nodes();
}

void MatrixGraph::write(std::ostream& os) const {
    for (int i = 0; i < (int)node_labels.size(); i++)
        for (int j = 0; j < (int)node_labels.size(); j++)
            for (const std::string& edge_label : adjacency[i][j])
                os << node_labels[i] << " " << edge_label << " " << node_labels[j] << ".\n";
}

void MatrixGraph::read(std::istream& is) {
    std::string a, edge_label, b;
    while (is >> a >> edge_label >> b) {
        if (!b.empty() && b.back() == '.') b.pop_back();
        insert_edge(a, edge_label, b);
    }
}

void MatrixGraph::clear() {
    node_labels.clear();
    adjacency.clear();
}

std::vector<std::string> MatrixGraph::get_nodes() const {
    return node_labels;
}

std::vector<std::string> MatrixGraph::get_neighbors(const std::string& from) const {
    int i = find_node(from);
    if (i == -1) return {};
    std::vector<std::string> result;
    for (int j = 0; j < (int)node_labels.size(); j++)
        if (!adjacency[i][j].empty())
            result.push_back(node_labels[j]);
    return result;
}

std::vector<std::string> MatrixGraph::get_neighbors_with_label(
    const std::string& from, const std::string& edge_label) const
{
    int i = find_node(from);
    if (i == -1) return {};
    std::vector<std::string> result;
    for (int j = 0; j < (int)node_labels.size(); j++)
        for (const std::string& lbl : adjacency[i][j])
            if (lbl == edge_label) {
                result.push_back(node_labels[j]);
                break;
            }
    return result;
}