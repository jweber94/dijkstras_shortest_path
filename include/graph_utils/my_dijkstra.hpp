#ifndef MYDIJKSTRA
#define MYDIJKSTRA

#include "graph_node.hpp"
#include <memory>
#include <vector>

class DijkstraShortestPath {
public:
  // constructors
  DijkstraShortestPath() = delete;
  DijkstraShortestPath(std::vector<std::shared_ptr<GraphNode>> input_graph);

  // destructors
  ~DijkstraShortestPath() = default;

  // methods
  double get_shortest_path_cost() const;
  std::vector<std::shared_ptr<GraphNode>> run_dijkstra();

private:
  std::vector<std::shared_ptr<GraphNode>> input_graph_;
  std::vector<std::shared_ptr<GraphNode>> shortest_path_sequence_;
  double shortest_path_cost_;
};

#endif /* MYDIJKSTRA */