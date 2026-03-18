#include "diamond.h"
#include <sstream>
#include <unordered_set>
#include <set>
#include <algorithm>

DiamondQuery read_query(std::istream& is) {
    DiamondQuery q;
    std::string line;

    auto parse_line = [](const std::string& line) {
        std::vector<std::string> tokens;
        std::istringstream ss(line);
        std::string tok;
        while (ss >> tok) {
            if (!tok.empty() && tok.back() == '.') tok.pop_back();
            if (!tok.empty()) tokens.push_back(tok);
        }
        return tokens;
    };

    if (std::getline(is, line)) q.even_labels = parse_line(line);
    if (std::getline(is, line)) q.odd_labels  = parse_line(line);
    return q;
}

static std::vector<std::string> follow_path(
    const Graph& g,
    const std::string& start,
    const std::vector<std::string>& labels)
{
    std::vector<std::string> current = {start};
    for (const std::string& lbl : labels) {
        std::vector<std::string> next;
        for (const std::string& node : current) {
            auto neighbors = g.get_neighbors_with_label(node, lbl);
            for (const std::string& nb : neighbors)
                next.push_back(nb);
        }
        if (next.empty()) return {};
        current = std::move(next);
    }
    return current;
}

std::vector<std::pair<std::string,std::string>>
find_diamond_pairs(const Graph& g, const DiamondQuery& q)
{
    if (q.even_labels.empty() || q.odd_labels.empty()) return {};
    if (q.even_labels.size() != q.odd_labels.size()) return {};

    std::vector<std::pair<std::string,std::string>> result;
    std::set<std::pair<std::string,std::string>> seen;

    for (const std::string& ni : g.get_nodes()) {
        auto even_ends = follow_path(g, ni, q.even_labels);
        if (even_ends.empty()) continue;
        auto odd_ends = follow_path(g, ni, q.odd_labels);
        if (odd_ends.empty()) continue;

        std::unordered_set<std::string> even_set(even_ends.begin(), even_ends.end());
        for (const std::string& nj : odd_ends) {
            if (even_set.count(nj)) {
                auto p = std::make_pair(ni, nj);
                if (!seen.count(p)) {
                    seen.insert(p);
                    result.push_back(p);
                }
            }
        }
    }
    return result;
}