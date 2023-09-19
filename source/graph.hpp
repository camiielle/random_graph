#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>
#include <random>
#include <unordered_map>
#include <vector>

// defines class Graph using adjacency list representation

class Graph {
  std::unordered_map<int, std::vector<int>> adjList_;

 public:
  Graph(std::unordered_map<int, std::vector<int>> const& adjList)
      : adjList_{adjList} {
    assert(!(adjList_.empty()));
  }

  // N.B. not risking narrowing with int as return type since parameter
  // numOfNodes is an int
  int size() const { return adjList_.size(); }
  std::vector<int>& operator[](int index) { return adjList_[index]; }
  void BFS();  // breadth first search
  void DFS();  // depth first search
};

void removeElement(std::vector<int>::iterator const& element,
                   std::vector<int>& vec);

std::vector<std::vector<int>>& generateRandomEdges(
    std::vector<std::vector<int>>& neighbors, int numOfNodes, int numOfEdges,
    unsigned int seed);

std::unordered_map<int, std::vector<int>>& fill(
    std::unordered_map<int, std::vector<int>>& adjList, int numOfNodes,
    int numOfEdges, unsigned int seed);

#endif