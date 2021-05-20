#ifndef MY_DIJKSTRA
#define MY_DIJKSTRA

#include "graph_node.hpp"
#include <memory>
#include <queue>
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
  std::vector<std::shared_ptr<GraphNode>>
  run_dijkstra(const GraphNode &start_node, const GraphNode &end_node);

private:
  std::vector<std::shared_ptr<GraphNode>> input_graph_;
  std::vector<std::shared_ptr<GraphNode>>
      shortest_path_sequence_; // Maybe convert this to a FiFo List
  std::priority_queue<GraphNode, std::vector<GraphNode>, CompGraphNode>
      open_set_;
  std::vector<std::shared_ptr<GraphNode>> closed_set;
  double shortest_path_cost_;
};

#endif /* MY_DIJKSTRA */