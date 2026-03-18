#include "scc.h"
#include <unordered_map>
#include <stack>
#include <algorithm>

struct VertexInfo {
    int index    = -1;
    int lowlink  = -1;
    bool onStack = false;
};

static void strongconnect(
    const std::string&                              v,
    const Graph&                                    g,
    std::unordered_map<std::string, VertexInfo>&    info,
    std::stack<std::string>&                        S,
    int&                                            counter,
    std::vector<std::vector<std::string>>&          sccs)
{
    auto& vi = info[v];
    vi.index   = counter;
    vi.lowlink = counter;
    counter++;
    S.push(v);
    vi.onStack = true;

    for (const std::string& w : g.get_neighbors(v)) {
        auto& wi = info[w];
        if (wi.index == -1) {
            strongconnect(w, g, info, S, counter, sccs);
            vi.lowlink = std::min(vi.lowlink, info[w].lowlink);
        } else if (wi.onStack) {
            vi.lowlink = std::min(vi.lowlink, wi.index);
        }
    }

    if (vi.lowlink == vi.index) {
        std::vector<std::string> scc;
        std::string w;
        do {
            w = S.top(); S.pop();
            info[w].onStack = false;
            scc.push_back(w);
        } while (w != v);
        sccs.push_back(std::move(scc));
    }
}

std::vector<std::vector<std::string>> find_sccs(const Graph& g) {
    std::unordered_map<std::string, VertexInfo> info;
    std::stack<std::string> S;
    int counter = 0;
    std::vector<std::vector<std::string>> sccs;

    for (const std::string& v : g.get_nodes())
        info[v];  // default-initialiser VertexInfo

    for (const std::string& v : g.get_nodes())
        if (info[v].index == -1)
            strongconnect(v, g, info, S, counter, sccs);

    return sccs;
}