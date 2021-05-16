#include "graph_class.hpp"

#include <iostream>
#include <time.h>

UndirectedGraph::UndirectedGraph(const size_t num_nodes,
                                 const double lower_weight,
                                 const double upper_weight,
                                 const double vertex_prob) {
  // get the run parameter
  this->lower_vertex_weight_ = lower_weight;
  this->upper_vertex_weight_ = upper_weight;
  this->vertex_prob_ = vertex_prob;
  this->num_nodes_ = num_nodes;

  this->avg_vertex_cost_ = 0;
  this->shortest_path_cost_ = -1;

  // preallocation
  this->vertex_weights_ =
      -(Eigen::MatrixXd::Identity(this->num_nodes_, this->num_nodes_));

  // initialize random graph vertex weights
  this->create_random_graph();

  // create graph nodes
  std::cout << "The random graph matrix is:\n" << this->vertex_weights_ << "\n";
  for (int i = 0; i < this->num_nodes_; i++) {
    Eigen::VectorXd temp_weights = this->vertex_weights_.row(i);
    std::cout << "temp_weights with index i=" << i << " are: \n"
              << temp_weights << "\n";
    std::shared_ptr<GraphNode> temp_node =
        std::make_shared<GraphNode>(i, temp_weights);
    this->graph_nodes_.push_back(temp_node);
  }

  // calculate graph statistics
  this->calculate_avg_vertex_weights();
}

UndirectedGraph::UndirectedGraph(const size_t num_nodes,
                                 const double lower_weight,
                                 const double upper_weight,
                                 const double vertex_prob,
                                 const std::string path_to_weights_file) {
  // get the run parameter
  this->lower_vertex_weight_ = lower_weight;
  this->upper_vertex_weight_ = upper_weight;
  this->vertex_prob_ = vertex_prob;
  this->num_nodes_ = num_nodes;

  std::cerr << "This constructor is not implemented yet.\n";
  throw std::logic_error("Constructor UndirectedGraph not implemented yet");
}

void UndirectedGraph::create_random_graph() {
  std::cout << "Creating random graph\n";
  // random graph initialization
  srand(time(
      0)); // set the seed - time(0) is the current system time based on seconds
  for (int i = 0; i < this->num_nodes_; i++) { // rows
    for (int j = 0; j < i; j++) {              // cols of the symetric matrix
      if (i == j) {
        continue; // stay at -1
      } else {
        double random_num_weight = (double)rand() / RAND_MAX;
        double temp_weight = this->lower_vertex_weight_ +
                             random_num_weight * (this->upper_vertex_weight_ -
                                                  this->lower_vertex_weight_);
        double random_num_acceptance = (double)rand() / RAND_MAX;
        this->vertex_weights_(i, j) =
            (random_num_acceptance < this->vertex_prob_) *
            temp_weight; // brackets get 0 or 1
        this->vertex_weights_(j, i) =
            (random_num_acceptance < this->vertex_prob_) *
            temp_weight; // since it is a symetric matrix
                         // if an vertex gets the value 0, we dont have a
                         // connection
      }
    }
  }
}

void UndirectedGraph::create_graph_based_on_file() {
  std::cerr << "This method is not implemented yet\n";
  throw std::logic_error(
      "Method create_graph_based_on_file not implemented yet");
}

void UndirectedGraph::calculate_avg_vertex_weights() {
  double temp_sum = 0;
  for (int i = 0; i < this->num_nodes_; i++) {
    temp_sum +=
        static_cast<double>(this->graph_nodes_[i]->get_weights().sum()) +
        1.0; // +1 since the self reference is based on -1 in the weights vector
  }
  this->avg_vertex_cost_ =
      temp_sum / (2.0 * static_cast<double>(this->num_nodes_));
}

double UndirectedGraph::get_shortest_path_costs() const {
  return this->shortest_path_cost_;
}

double UndirectedGraph::get_avg_vertex_costs() const {
  return this->avg_vertex_cost_;
}

void UndirectedGraph::run_dijkstra() {
  std::cout << "started dijkstra's algorithm\n";
  // FIXME

  std::cout << "finished dijkstra's algorithm\n";
}
