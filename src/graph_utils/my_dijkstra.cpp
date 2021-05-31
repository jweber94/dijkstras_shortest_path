#include "my_dijkstra.hpp"

#include <algorithm>
#include <iostream>
#include <map>
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
DijkstraShortestPath::run_dijkstra(const int &start_node, const int &end_node) {
  std::vector<int> closed_set_idxs;
  std::vector<int> open_set_idxs;
  std::priority_queue<std::shared_ptr<GraphNode>,
                      std::vector<std::shared_ptr<GraphNode>>, CompGraphNode>
      open_set;
  Eigen::VectorXd temp_weights(this->input_graph_.size());
  std::vector<std::shared_ptr<GraphNode>> result_nodes;

  closed_set_idxs.push_back(start_node);
  temp_weights = this->input_graph_[start_node]->get_weights();
  open_set.push(this->input_graph_[start_node]);

  while (
      !(std::count(closed_set_idxs.begin(), closed_set_idxs.end(), end_node)))
  // as long as the finish node is not contained in the closed set, do the
  // following
  {
    // get the greedy node from the open set
    std::shared_ptr<GraphNode> current_node = open_set.top();
    temp_weights = current_node->get_weights();
    // put the object to the closed set, since it got expanded now
    open_set.pop();
    open_set_idxs.erase(std::remove(open_set_idxs.begin(), open_set_idxs.end(),
                                    current_node->get_node_number()),
                        open_set_idxs.end());
    closed_set_idxs.push_back(current_node->get_node_number());

    for (int i = 0; i < this->input_graph_.size(); i++) {
      assert(temp_weights.size() == this->input_graph_.size());
      if ((temp_weights(i) == -1) || (temp_weights(i) == 0) ||
          (std::count(closed_set_idxs.begin(), closed_set_idxs.end(), i))) {
        // no connection --> points to itself || no connection || already in the
        // closed set
        continue;
      }

      bool in_open_set =
          std::count(open_set_idxs.begin(), open_set_idxs.end(), i);
      double temp_weight_to_node;
      temp_weight_to_node =
          current_node->get_last_cummulated_weight() + temp_weights(i);

      // connection exists
      if (in_open_set &&
          (temp_weight_to_node <=
           this->input_graph_[i]->get_last_cummulated_weight())) {
        // already in the open set but the new connection has a less overall
        // weight
        std::cout << "new cheaper path to " << i << " found\n";
        this->input_graph_[i]->set_predecessor_node(i);
        this->input_graph_[i]->set_cummulated_weight(temp_weight_to_node);
      } else if (in_open_set &&
                 (temp_weight_to_node >
                  this->input_graph_[i]->get_last_cummulated_weight())) {
        // already in the open set but no update needed
        std::cout << "no cheaper path for " << i << "\n";
        continue;
      } else {
        // currently not contained in the open set
        std::cout << "new node " << i << "added to the open set\n";
        this->input_graph_[i]->set_predecessor_node(
            current_node->get_node_number());
        this->input_graph_[i]->set_cummulated_weight(temp_weight_to_node);
        open_set.push(this->input_graph_[i]);
        open_set_idxs.push_back(i);
      }
    }
  }

  // get the shortest path information
  this->shortest_path_cost_ =
      this->input_graph_[end_node]->get_last_cummulated_weight();
  this->traverse_shortest_path(
      start_node, end_node); // creates the this->shortest_path_sequence_
  this->temp_start_idx_ = start_node;
  this->temp_end_idx_ = end_node;

  return this->shortest_path_sequence_;
}

void DijkstraShortestPath::traverse_shortest_path(const int &start,
                                                  const int &end) {
  std::cout << "Traverse the path.\n";
  bool finished = false;
  int next_idx;
  int temp_next_idx;

  this->shortest_path_idxs_.push_back(
      this->input_graph_[end]->get_node_number());
  this->shortest_path_sequence_.push_back(this->input_graph_[end]);

  next_idx = this->input_graph_[end]->get_predecessor_node();

  while (next_idx != start) {
    std::cout << "next_idx is: " << next_idx << "\n";
    this->shortest_path_idxs_.push_back(
        this->input_graph_[next_idx]->get_node_number());
    this->shortest_path_sequence_.push_back(this->input_graph_[next_idx]);

    temp_next_idx = this->input_graph_[next_idx]->get_predecessor_node();
    // debug
    if (next_idx == temp_next_idx) {
      std::cerr << "Something went wrong\n";
      exit(0);
    }
    next_idx = temp_next_idx;
  }
  // add the start node after finishing traversing back
  this->shortest_path_idxs_.push_back(
      this->input_graph_[next_idx]->get_node_number());
  this->shortest_path_sequence_.push_back(this->input_graph_[next_idx]);

  // invert the vectors to start from the start node and end with the end node
  std::reverse(this->shortest_path_idxs_.begin(),
               this->shortest_path_idxs_.end());
  std::reverse(this->shortest_path_sequence_.begin(),
               this->shortest_path_sequence_.end());
}

void DijkstraShortestPath::print_shortest_path() const {
  std::cout << "The shortest path from node " << this->temp_start_idx_ << " to "
            << this->temp_end_idx_ << " is:\n";
  for (int i = 0; i < this->shortest_path_sequence_.size(); i++) {
    std::cout << this->shortest_path_idxs_[i] << "\n";
  }
  std::cout << "With the overall costs of " << this->shortest_path_cost_
            << "\n";
}

std::vector<int> DijkstraShortestPath::get_shortest_path_idxs() const {
  return this->shortest_path_idxs_;
}
