#pragma once
#include "graph.h"
#include <string>
#include <vector>

/**
 * Compute strongly connected components using Tarjan's algorithm.
 *
 * Returns a list of SCCs; each SCC is a list of node labels.
 * SCCs are returned in reverse topological order (the SCC containing
 * a sink node comes first).
 *
 * @param g       The graph (read-only).
 * @param verbose If true, print progress and results to stdout.
 */
std::vector<std::vector<std::string>>
tarjan_scc(const Graph& g, bool verbose = false);
