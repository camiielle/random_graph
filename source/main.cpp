#include <chrono>
#include <iostream>

#include "graph.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
  try {
    // instantiates a simple graph with numOfNodes represented through
    // adjacency list with randomly generated edges

    // default values are modified only if an input value is specified
    int numOfNodes{50};
    int numOfEdges{4};
    bool show_help{false};
    std::random_device rd;
    auto const seed{rd()};

    // Parser with multiple option arguments and help option
    auto parser = get_parser(numOfNodes, numOfEdges, show_help);
    // Parses the arguments
    auto result = parser.parse({argc, argv});
    // Checks that arguments were valid
    if (!result) {
      std::cerr << "Error occurred in command line: " << result.message() << '\n'
                << parser << '\n';
      return EXIT_FAILURE;
    }
    // Shows the help if asked for
    if (show_help) {
      std::cout << parser << '\n';
      return EXIT_SUCCESS;
    }

    assert(result && (!show_help));

    std::unordered_map<int, std::vector<int>> adjList{};
    Graph graph{fill(adjList, numOfNodes, numOfEdges, seed)};

    // applies traversal algorithms bfs and dfs (starting from random node) and
    // times them:

    std::default_random_engine eng(seed);
    // transforms the random unsigned int generated by gen into a random int
    // in the closed interval [a,b]
    std::uniform_int_distribution<> randomNeighbor(0, 19);
    int start{randomNeighbor(eng)};
    std::vector<int> bfs_traversal{};
    auto t1_bfs{std::chrono::high_resolution_clock::now()};
    graph.bfs(start, bfs_traversal);
    auto t2_bfs{std::chrono::high_resolution_clock::now()};
    std::vector<int> dfs_traversal{};
    auto t1_dfs{std::chrono::high_resolution_clock::now()};
    graph.dfs(start, dfs_traversal);
    auto t2_dfs{std::chrono::high_resolution_clock::now()};

    // printing the traversals
    std::cout << "\nBFS traversal:\n";
    printTraversal(bfs_traversal);
    std::cout << "\n\nDFS traversal:\n";
    printTraversal(dfs_traversal);

    // printing execution times
    auto duration_bfs =
        std::chrono::duration_cast<std::chrono::microseconds>(t2_bfs - t1_bfs);
    std::cout << "\n\nBFS Execution time: " << duration_bfs.count()
              << " microseconds";
    auto duration_dfs =
        std::chrono::duration_cast<std::chrono::microseconds>(t2_dfs - t1_dfs);
    std::cout << "\n\nDFS Execution time: " << duration_dfs.count()
              << " microseconds\n\n";

  } catch (std::exception const& err) {
    std::cerr << "An error occurred: " << err.what() << '\n';
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "An unknown error occurred\n";
    return EXIT_FAILURE;
  }
}