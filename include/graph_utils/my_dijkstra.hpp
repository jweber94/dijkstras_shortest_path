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
  void print_shortest_path() const;
  std::vector<std::shared_ptr<GraphNode>> run_dijkstra(const int &start_idx,
                                                       const int &end_idx);
  std::vector<int> get_shortest_path_idxs() const;

private:
  void traverse_shortest_path(const int &start, const int &end);

  std::vector<std::shared_ptr<GraphNode>>
      input_graph_; // the node numbers are defined by the index within the
                    // vector
  std::vector<std::shared_ptr<GraphNode>> shortest_path_sequence_;
  std::vector<int> shortest_path_idxs_;
  std::vector<std::shared_ptr<GraphNode>> closed_set;
  double shortest_path_cost_;
  int temp_start_idx_;
  int temp_end_idx_;
};

#endif /* MY_DIJKSTRA */