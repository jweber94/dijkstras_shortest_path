#include "my_dijkstra.hpp"

#include <iostream>
#include <stdexcept>

DijkstraShortestPath::DijkstraShortestPath(
    std::vector<std::shared_ptr<GraphNode>> input_graph) {
  // initialize
  this->shortest_path_cost_ = 0;
  this->input_graph_ = input_graph;
}

double DijkstraShortestPath::get_shortest_path_cost() const {
  return this->shortest_path_cost_;
}

std::vector<std::shared_ptr<GraphNode>>
DijkstraShortestPath::run_dijkstra(const GraphNode &start_node,
                                   const GraphNode &end_node) {
  // DEBUG/TEST This is just test code for the data pipeline
  Eigen::VectorXd test_vec(3);
  test_vec << 2.1, 1.1, 5.5;
  std::shared_ptr<GraphNode> temp_node =
      std::make_shared<GraphNode>(2, test_vec);
  std::vector<std::shared_ptr<GraphNode>> result;
  result.push_back(temp_node);

  // FIXME: run the calculation of dijkstras algorithm
  // TODO

  // setting the costs for the calculated shortest path
  this->shortest_path_cost_ = -1.0; // FIXME

  return result;
}
