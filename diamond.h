#pragma once
#include "graph.h"
#include <vector>
#include <string>

struct DiamondQuery {
    std::vector<std::string> even_labels;  // r0, r2, r4, ...
    std::vector<std::string> odd_labels;   // r1, r3, r5, ...
};

DiamondQuery read_query(std::istream& is);

std::vector<std::pair<std::string,std::string>>
find_diamond_pairs(const Graph& g, const DiamondQuery& q);