#pragma once
#include "graph.h"
#include <string>
#include <vector>
#include <utility>

/**
 * Find all node pairs (ni, nj) such that there is BOTH
 *   a path  ni -[path1[0]]-> ... -[path1[m-1]]-> nj
 *   AND
 *   a path  ni -[path2[0]]-> ... -[path2[m-1]]-> nj
 *
 * @param g       The graph (read-only).
 * @param path1   Edge-label sequence for the first path  (r0, r2, r4 ...).
 * @param path2   Edge-label sequence for the second path (r1, r3, r5 ...).
 * @param verbose If true, print results and timing to stdout.
 * @return        List of (ni, nj) pairs satisfying the diamond condition.
 */
std::vector<std::pair<std::string,std::string>>
diamond_query(const Graph& g,
              const std::vector<std::string>& path1,
              const std::vector<std::string>& path2,
              bool verbose = false);

/**
 * Read a query file with two lines of space-separated edge labels,
 * each line terminated by '.'.
 * Populates path1 and path2.
 */
void read_query(std::istream& is,
                std::vector<std::string>& path1,
                std::vector<std::string>& path2);
