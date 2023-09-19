#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.hpp"

TEST_CASE("testing Graph") {
  std::unordered_map<int, std::vector<int>> adjList0{
      {0, {2, 3}}, {1, {2}}, {2, {0, 1, 3}}, {3, {0, 2}}};
  std::unordered_map<int, std::vector<int>> adjList1{
      {0, {1}}, {1, {0, 2}}, {2, {1}}};
  std::unordered_map<int, std::vector<int>> adjList2{
      {0, {2, 3, 4}}, {1, {2}},    {2, {0, 1, 3}}, {3, {0, 2}},
      {4, {0, 5}},    {5, {4, 6}}, {6, {5}}};

  Graph g0{adjList0};
  Graph g1{adjList1};
  Graph g2{adjList2};

  SUBCASE("testing size") {
    CHECK(g0.size() == 4);
    CHECK(g1.size() == 3);
    CHECK(g2.size() == 7);
  }

  SUBCASE("testing constructor and subscript operator") {
    CHECK(g0[0] == std::vector<int>{2, 3});
    CHECK(g0[1] == std::vector<int>{2});
    CHECK(g0[2] == std::vector<int>{0, 1, 3});
    CHECK(g0[3] == std::vector<int>{0, 2});

    CHECK(g1[0] == std::vector<int>{1});
    CHECK(g1[1] == std::vector<int>{0, 2});
    CHECK(g1[2] == std::vector<int>{1});

    CHECK(g2[0] == std::vector<int>{2, 3, 4});
    CHECK(g2[1] == std::vector<int>{2});
    CHECK(g2[2] == std::vector<int>{0, 1, 3});
    CHECK(g2[3] == std::vector<int>{0, 2});
    CHECK(g2[4] == std::vector<int>{0, 5});
    CHECK(g2[5] == std::vector<int>{4, 6});
    CHECK(g2[6] == std::vector<int>{5});
  }
}

TEST_CASE("testing removeElement") {
  std::vector<int> v0{0, 1, 2, 3, 4};
  std::vector<int> v1{5, 2, 8, 7, 6, 9};

  removeElement(v0.begin() + 3, v0);
  CHECK(v0.size() == 4);
  CHECK(v0 == std::vector<int>{0, 1, 2, 4});

  removeElement(v1.begin() + 5, v1);
  CHECK(v1.size() == 5);
  CHECK(v1 == std::vector<int>{5, 2, 8, 7, 6});
}

TEST_CASE("testing fill") {
  std::unordered_map<int, std::vector<int>> adjList{};
  int numOfNodes{50};
  int numOfEdges{3};
  std::random_device rd;
  auto const seed{rd()};

  fill(adjList, numOfNodes, numOfEdges, seed);

  CHECK(adjList.size() == numOfNodes);

  for (int i{}; i != numOfNodes; ++i) {
    CHECK(std::is_sorted(adjList[i].begin(), adjList[i].end()));
  }

  for (int i{}; i != numOfNodes; ++i) {  // no duplicates
    CHECK((std::adjacent_find(adjList[i].begin(), adjList[i].end())) ==
          adjList[i].end());
  }

  for (int i{}; i != numOfNodes; ++i) {  // at least one neighbor
    CHECK(adjList[i].size() > 0ul);
  }
}
