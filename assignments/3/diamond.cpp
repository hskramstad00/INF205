#include "diamond.h"
#include <iostream>
#include <unordered_set>
#include <sstream>

// ── Helpers ──────────────────────────────────────────────────────────────────

/**
 * Starting from a set of nodes, follow the label sequence one step at a time.
 * Returns the set of nodes reachable from @p start_nodes by traversing edges
 * with labels labels[0], labels[1], ..., labels[m-1] in order.
 */
static std::unordered_set<std::string>
follow_path(const Graph& g,
            const std::string& start,
            const std::vector<std::string>& labels) {
    std::unordered_set<std::string> current;
    current.insert(start);

    for (const auto& lbl : labels) {
        std::unordered_set<std::string> next;
        for (const auto& node : current) {
            for (const auto& succ : g.successors(node, lbl))
                next.insert(succ);
        }
        current = std::move(next);
        if (current.empty()) break;
    }
    return current;
}

// ── Public API ───────────────────────────────────────────────────────────────

std::vector<std::pair<std::string,std::string>>
diamond_query(const Graph& g,
              const std::vector<std::string>& path1,
              const std::vector<std::string>& path2,
              bool verbose) {
    std::vector<std::pair<std::string,std::string>> result;

    if (path1.size() != path2.size()) {
        std::cerr << "diamond_query: path1 and path2 must have the same length.\n";
        return result;
    }

    const auto all_nodes = g.nodes();

    for (const auto& ni : all_nodes) {
        // All nodes reachable via path1 labels from ni
        auto ends1 = follow_path(g, ni, path1);
        if (ends1.empty()) continue;

        // All nodes reachable via path2 labels from ni
        auto ends2 = follow_path(g, ni, path2);
        if (ends2.empty()) continue;

        // Intersection = valid nj targets
        for (const auto& nj : ends1)
            if (ends2.count(nj))
                result.emplace_back(ni, nj);
    }

    if (verbose) {
        std::cout << "Diamond pairs (" << result.size() << " found):\n";
        for (const auto& [ni, nj] : result)
            std::cout << "  " << ni << " -> " << nj << "\n";
    }

    return result;
}

void read_query(std::istream& is,
                std::vector<std::string>& path1,
                std::vector<std::string>& path2) {
    path1.clear();
    path2.clear();

    std::string line;
    int line_no = 0;

    while (std::getline(is, line) && line_no < 2) {
        // Remove trailing '.' and whitespace
        while (!line.empty() && (line.back() == '.' || line.back() == '\r'
                                  || line.back() == ' '))
            line.pop_back();

        std::istringstream ss(line);
        std::string token;
        while (ss >> token) {
            if (line_no == 0) path1.push_back(token);
            else              path2.push_back(token);
        }
        ++line_no;
    }
}
