#include "adjacencyMatrixGraph.h"
#include <iostream>
#include <stdexcept>

// ---------- Private hjelpemetoder ----------

int MatrixGraph::find_node(const std::string& label) const {
    for(int i = 0; i < (int)node_labels.size(); i++)
        if(node_labels[i] == label) return i;
    return -1; // ikke funnet
}

int MatrixGraph::find_or_create_node(const std::string& label) {
    int i = find_node(label);
    if(i != -1) return i;

    // Legg til ny node
    node_labels.push_back(label);
    int n = node_labels.size();

    // Utvid matrisen: legg til ny kolonne i hver eksisterende rad
    for(auto& row : adjacency)
        row.push_back({});

    // Legg til ny rad (en kolonne per node inkludert den nye)
    adjacency.push_back(std::vector<std::list<std::string>>(n));

    return n - 1;
}

void MatrixGraph::remove_isolated_nodes() {
    // En node er isolert om hele raden og kolonnen er tomme
    bool found = true;
    while(found) {
        found = false;
        for(int i = 0; i < (int)node_labels.size(); i++) {
            bool isolated = true;

            // Sjekk raden (kanter ut fra node i)
            for(int j = 0; j < (int)node_labels.size(); j++)
                if(!adjacency[i][j].empty()) { isolated = false; break; }

            // Sjekk kolonnen (kanter inn til node i)
            if(isolated)
                for(int j = 0; j < (int)node_labels.size(); j++)
                    if(!adjacency[j][i].empty()) { isolated = false; break; }

            if(isolated) {
                // Fjern rad i
                adjacency.erase(adjacency.begin() + i);
                // Fjern kolonne i fra alle rader
                for(auto& row : adjacency)
                    row.erase(row.begin() + i);
                node_labels.erase(node_labels.begin() + i);
                found = true;
                break; // start på nytt siden indekser har endret seg
            }
        }
    }
}

// ---------- insert_edge ----------

void MatrixGraph::insert_edge(std::string a, std::string edge_label, std::string b) {
    int i = find_or_create_node(a);
    int j = find_or_create_node(b);
    adjacency[i][j].push_back(edge_label);
}

// ---------- disconnect ----------

void MatrixGraph::disconnect(std::string a, std::string b) {
    int i = find_node(a);
    int j = find_node(b);
    if(i == -1 || j == -1) return;

    adjacency[i][j].clear(); // slett alle kanter fra a til b
    remove_isolated_nodes();
}

// ---------- remove_node ----------

void MatrixGraph::remove_node(std::string label) {
    int i = find_node(label);
    if(i == -1) return;

    // Fjern rad i
    adjacency.erase(adjacency.begin() + i);
    // Fjern kolonne i fra alle rader
    for(auto& row : adjacency)
        row.erase(row.begin() + i);

    node_labels.erase(node_labels.begin() + i);
    remove_isolated_nodes();
}

// ---------- Fil-I/O ----------

void MatrixGraph::write(std::ostream& os) const {
    for(int i = 0; i < (int)node_labels.size(); i++)
        for(int j = 0; j < (int)node_labels.size(); j++)
            for(const std::string& edge_label : adjacency[i][j])
                os << node_labels[i] << " " << edge_label << " " << node_labels[j] << "\n";
}

void MatrixGraph::read(std::istream& is) {
    std::string a, edge_label, b;
    while(is >> a >> edge_label >> b)
        insert_edge(a, edge_label, b);
}