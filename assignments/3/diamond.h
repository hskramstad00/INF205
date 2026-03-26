#pragma once
#include "graph.h"
#include <string>
#include <vector>
#include <utility>


std::vector<std::pair<std::string,std::string>>
diamond_query(const Graph& g,
              const std::vector<std::string>& path1,
              const std::vector<std::string>& path2,
              bool verbose = false);


void read_query(std::istream& is,
                std::vector<std::string>& path1,
                std::vector<std::string>& path2);
