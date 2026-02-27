#include "GraphMatrix.h"

#include <fstream>
#include <stdexcept>

// Et "ikke funnet"-signal for size_t
static constexpr std::size_t NPOS = static_cast<std::size_t>(-1);

// -------------------- private helpers --------------------

std::size_t GraphMatrix::find_index_(const std::string& label) const {
    auto it = index_.find(label);
    return (it == index_.end()) ? NPOS : it->second;
}

std::size_t GraphMatrix::get_or_add_index_(const std::string& label) {
    if (auto it = index_.find(label); it != index_.end()) return it->second;

    const std::size_t new_i = labels_.size();
    labels_.push_back(label);
    index_[label] = new_i;

    // Utvid matrisen:
    // 1) legg til ny kolonne (tom celle) i alle eksisterende rader
    for (auto& row : adj_) {
        row.emplace_back(); // ny vector<string> for kolonnen
    }

    // 2) legg til ny rad med riktig bredde (labels_.size())
    adj_.emplace_back(labels_.size(), std::vector<std::string>{});

    return new_i;
}

// Fjern node med indeks idx: fjern label, rad, kolonne og rebuild index_
void GraphMatrix::remove_index_(std::size_t idx) {
    if (idx >= labels_.size()) return;

    // Fjern label
    labels_.erase(labels_.begin() + static_cast<std::ptrdiff_t>(idx));

    // Fjern rad idx
    adj_.erase(adj_.begin() + static_cast<std::ptrdiff_t>(idx));

    // Fjern kolonne idx i hver rad
    for (auto& row : adj_) {
        row.erase(row.begin() + static_cast<std::ptrdiff_t>(idx));
    }

    // Rebuild indeks-map
    index_.clear();
    for (std::size_t i = 0; i < labels_.size(); ++i) {
        index_[labels_[i]] = i;
    }
}

// Slett isolerte noder: noder uten inn- og utkanter
void GraphMatrix::cleanup_isolated_nodes_() {
    // Siden fjerning endrer indekser: loop fra slutten, og kjør til stabilt
    bool removed_any = true;
    while (removed_any) {
        removed_any = false;

        for (std::size_t k = labels_.size(); k-- > 0; ) {
            bool has_any_edge = false;

            // Sjekk utkanter fra k
            for (std::size_t j = 0; j < labels_.size(); ++j) {
                if (!adj_[k][j].empty()) {
                    has_any_edge = true;
                    break;
                }
            }

            // Sjekk innkanter til k hvis ingen utkant ble funnet
            if (!has_any_edge) {
                for (std::size_t i = 0; i < labels_.size(); ++i) {
                    if (!adj_[i][k].empty()) {
                        has_any_edge = true;
                        break;
                    }
                }
            }

            if (!has_any_edge) {
                remove_index_(k);
                removed_any = true;
                break; // start på nytt (indekser endret)
            }
        }
    }
}

// -------------------- Graph API --------------------

void GraphMatrix::insert_edge(const std::string& node_a_label,
                              const std::string& edge_label,
                              const std::string& node_b_label) {
    const std::size_t i = get_or_add_index_(node_a_label);
    const std::size_t j = get_or_add_index_(node_b_label);

    adj_[i][j].push_back(edge_label);
}

void GraphMatrix::disconnect(const std::string& node_a_label,
                             const std::string& node_b_label) {
    const std::size_t i = find_index_(node_a_label);
    const std::size_t j = find_index_(node_b_label);
    if (i == NPOS || j == NPOS) return;

    // Slett alle kanter fra i -> j (kun den retningen)
    adj_[i][j].clear();

    cleanup_isolated_nodes_();
}

void GraphMatrix::remove_node(const std::string& node_label) {
    const std::size_t idx = find_index_(node_label);
    if (idx == NPOS) return;

    // remove_index_ fjerner noden + alle kanter inn/ut (via rad/kolonne)
    remove_index_(idx);

    cleanup_isolated_nodes_();
}

void GraphMatrix::read_from_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Could not open file for reading: " + path);

    std::string a, el, b;
    while (in >> a >> el >> b) {
        insert_edge(a, el, b);
    }
}

void GraphMatrix::write_to_file(const std::string& path) const {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Could not open file for writing: " + path);

    for (std::size_t i = 0; i < labels_.size(); ++i) {
        for (std::size_t j = 0; j < labels_.size(); ++j) {
            for (const auto& el : adj_[i][j]) {
                out << labels_[i] << " " << el << " " << labels_[j] << "\n";
            }
        }
    }
}