#ifndef MY_DIJKSTRA
#define MY_DIJKSTRA

#include "graph_node.hpp"
#include <memory>
#include <queue>
#include <vector>

class CompOpenSet {
public:
  CompOpenSet() = default;

  int operator()(const std::pair<int, double> &node_1, const std::pair<int, double> &node_2) {
    bool result = true;
    // ToDo: create comparison function for the node order to create a min_heap
    return result;
  }
};


class DijkstraShortestPath {
public:
  // constructors
  DijkstraShortestPath() = delete;
  DijkstraShortestPath(std::vector<std::shared_ptr<GraphNode>> input_graph);

  // destructors
  ~DijkstraShortestPath() = default;

  // methods
  double get_shortest_path_cost() const;
  //std::vector<std::shared_ptr<GraphNode>> run_dijkstra(const GraphNode &start_node, const GraphNode &end_node);
  std::vector<std::shared_ptr<GraphNode>> run_dijkstra(const int &start_idx, const int &end_idx);

private:
  std::vector<std::shared_ptr<GraphNode>> input_graph_; // the node numbers are defined by the index within the vector
  std::vector<std::shared_ptr<GraphNode>>
      shortest_path_sequence_; // Maybe convert this to a FiFo List
  std::priority_queue<GraphNode, std::vector<GraphNode>, CompGraphNode>
      open_set_;
  std::vector<std::shared_ptr<GraphNode>> closed_set;
  double shortest_path_cost_;
};

#endif /* MY_DIJKSTRA */