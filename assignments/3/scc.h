#pragma once
#include "graph.h"
#include <string>
#include <vector>

std::vector<std::vector<std::string>>
tarjan_scc(const Graph& g, bool verbose = false);
