#ifndef PARSER_HPP
#define PARSER_HPP

#include <iomanip>
#include <iostream>
#include <lyra/lyra.hpp>

inline auto get_parser(int& numOfNodes, int& numOfEdges, bool& show_help) {
  return lyra::cli{
      lyra::help(show_help) |
      lyra::opt(numOfNodes, "number-of-nodes")["-n"]["--nodes"](
          "Set number of nodes - must be greater than 1 "
          "[Default value is 50]") |
      lyra::opt(numOfEdges, "number-of-edges")["-e"]["--edges"](
          "Set number of edges  - must be greater than 0  [Default value is "
          "4]")};
}

#endif