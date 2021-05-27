#include "my_dijkstra.hpp"

#include <iostream>
#include <stdexcept>
#include <map>

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
DijkstraShortestPath::run_dijkstra(const int &start_node,
                                   const int &end_node) {
  /*
  // test/debug
  std::cout << "Start node: " << this->input_graph_[start_node]->get_node_number() << ", with the weights:\n" << this->input_graph_[start_node]->get_weights() << "\n"; 
  std::cout << "End node: " << this->input_graph_[end_node]->get_node_number() << ", with the weights:\n" << this->input_graph_[end_node]->get_weights() << "\n";
  */

  std::vector<std::shared_ptr<GraphNode> > result_nodes;
  std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double> >, CompOpenSet>
      open_set;
  std::vector<int> closed_set_idxs;
  Eigen::VectorXd temp_weights(this->input_graph_.size()); 

  closed_set_idxs.push_back(start_node);
  temp_weights = this->input_graph_[start_node]->get_weights(); 
  
  while (!(std::count(closed_set_idxs.begin(), closed_set_idxs.end(), end_node)))
  {
    for (int i = 0; i < this->input_graph_.size(); i++){
      // look throu all neighbors of a node and check if the current distance in the open set is less then a new one from the node
       
    }







    closed_set_idxs.push_back(end_node); 
    // as long as the end node is not contained within the closed set --> Do the iteration
    
  }
  


  // setting the costs for the calculated shortest path
  this->shortest_path_cost_ = -1.0; // FIXME

  // create/copy the nodes to the result vector

  return result_nodes;
}
