#include "graph_class.hpp"
#include "my_dijkstra.hpp"

#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <time.h>

UndirectedGraph::UndirectedGraph(const size_t num_nodes,
                                 const double lower_weight,
                                 const double upper_weight,
                                 const double vertex_prob,
                                 const int max_trials) {
  int init_counter = 0;
  bool not_connected = true;

  // get the run parameter
  this->lower_vertex_weight_ = lower_weight;
  this->upper_vertex_weight_ = upper_weight;
  this->vertex_prob_ = vertex_prob;
  this->num_nodes_ = num_nodes;

  this->avg_vertex_cost_ = 0;
  this->shortest_path_cost_ = -1;
  this->dijkstra_run_ = false;

  // preallocation
  this->vertex_weights_ =
      -(Eigen::MatrixXd::Identity(this->num_nodes_, this->num_nodes_));
  this->connection_matrix_.resize(this->num_nodes_, this->num_nodes_);

  // initialize random graph vertex weights
  while ((init_counter < max_trials) && not_connected) {
    this->create_random_graph();

    std::cout << "The random graph is:\n"
              << this->vertex_weights_ << "\n with the connection matrix:\n"
              << this->connection_matrix_ << "\n"; // Debug output
    not_connected = !(this->is_connected());
    init_counter++;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(1000)); // sleep for one secound because the
                                          // seed changes with every second
  }

  if (not_connected) {
    std::cerr << "Could not generate a valid graph. Plase consider adjusting "
                 "the acceptance threshold\n";
    exit(0);
  } else {
    std::cout << "Connected graph after " << init_counter << " iterations\n";
  }

  // create graph nodes
  for (int i = 0; i < this->num_nodes_; i++) {
    Eigen::VectorXd temp_weights = this->vertex_weights_.row(i);
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

  double random_num_weight;
  double temp_weight;
  double random_num_acceptance;

  // run settings
  this->num_edges_ = 0;
  srand(time(
      0)); // set the seed - time(0) is the current system time based on seconds

  for (int i = 0; i < this->num_nodes_; i++) { // rows
    for (int j = 0; j <= i; j++) {             // cols of the symetric matrix
      if (i == j) {
        this->connection_matrix_(i, j) = true;
        continue; // stay at -1 for the weight Matrix
      } else {
        random_num_weight = (double)rand() / RAND_MAX;
        temp_weight = this->lower_vertex_weight_ +
                      random_num_weight * (this->upper_vertex_weight_ -
                                           this->lower_vertex_weight_);
        random_num_acceptance = (double)rand() / RAND_MAX;

        // connection matrix
        this->connection_matrix_(i, j) =
            (random_num_acceptance < this->vertex_prob_);
        this->connection_matrix_(j, i) =
            (random_num_acceptance < this->vertex_prob_);

        this->num_edges_ += static_cast<std::size_t>(
            (random_num_acceptance < this->vertex_prob_));

        // weight matrix
        this->vertex_weights_(i, j) =
            this->connection_matrix_(i, j) * temp_weight;
        this->vertex_weights_(j, i) =
            this->connection_matrix_(j, i) * temp_weight;
        // since it is a symetric matrix if an vertex gets the value 0, we dont
        // have a connection
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
  std::cout << "Num edges: " << this->num_edges_ << "\n";
  for (int i = 0; i < this->num_nodes_; i++) {
    temp_sum +=
        static_cast<double>(this->graph_nodes_[i]->get_weights().sum()) +
        1.0; // +1 since the self reference is based on -1 in the weights vector
  }
  this->avg_vertex_cost_ =
      temp_sum / (2.0 * static_cast<double>(this->num_edges_));
}

double UndirectedGraph::get_shortest_path_costs() const {
  if (!this->dijkstra_run_) {
    std::cerr << "could not call get_shortest_path_costs() - please call "
                 "run_dijkstra() before calling this method.\n";
    return -1.0;
  } else {
    return this->shortest_path_cost_;
  }
}

double UndirectedGraph::get_avg_vertex_costs() const {
  return this->avg_vertex_cost_;
}

bool UndirectedGraph::is_connected() const {
  std::size_t c_size = 0; // size of the closed set
  std::size_t old_size;
  bool open[this->num_nodes_]{};
  bool close[this->num_nodes_]{};

  while (c_size < this->num_nodes_) {
    // as long as the closed set is smaller then the number of nodes in the
    // graph
    for (int i = 0; i < this->num_nodes_; ++i) {
      // go throu all possible neighbours of a node
      old_size = c_size; // save the old closed set size to check, if new nodes
                         // come during the check-run

      if (open[i] && (close[i] == false)) {
        // check if the the node (defined by index) if in the open set and NOT
        // in the closed set
        close[i] = true;
        c_size++;
      }
      // look for new elements in the open set
      for (int j = 0; j < this->num_nodes_; ++j) {
        open[j] = ((open[j] || this->connection_matrix_(i, j)) && (i != j));
        // if j is currently in the open set (open[j]=true), then it should
        // remain in the open set if the graph says that there is a connection,
        // add the node j to the open set
      }
    }
    if (c_size == this->num_nodes_) {
      return true; // connected
    }
    if (old_size == c_size) {
      return false; // not connected
    }
  }
}

void UndirectedGraph::find_path(const int & start_idx, const int & finish_idx) {
  DijkstraShortestPath dijkstra_calculator(this->graph_nodes_);
  
  if (! this->valid_start_end_nodes(start_idx, finish_idx)){
    std::cerr << "No valid start or finish node was given!\n"; 
    throw std::logic_error("No valid start nodes were given!") ; 
    exit(0);
  }

  this->shortest_path_nodes_ = dijkstra_calculator.run_dijkstra(start_idx, finish_idx); 

  this->shortest_path_cost_ = dijkstra_calculator.get_shortest_path_cost();

  this->dijkstra_run_ = true; // set flag variable to true
}

std::vector<size_t> UndirectedGraph::get_shortest_path_idxs() const {
  std::vector<size_t> result_idxs;
  std::cout << "Size of the shortest path: "
            << this->shortest_path_nodes_.size() << "\n";
  for (int i = 0; i < this->shortest_path_nodes_.size(); i++) {
    result_idxs.push_back(this->shortest_path_nodes_[i]->get_node_number());
  }
  return result_idxs;
}

void UndirectedGraph::print_shortest_path_idxs() const {
  std::cout << "The shortest path indices are:\n";
  for (int i = 0; i < this->shortest_path_nodes_.size(); i++) {
    std::cout << this->shortest_path_nodes_[i]->get_node_number() << "\n";
  }
}

void UndirectedGraph::print_weight_matrix() const {
  std::cout << "The vertex matrix of the graph is:\n"
            << this->vertex_weights_ << "\n";
}

bool UndirectedGraph::valid_start_end_nodes(const int & start_node_idx, const int & end_node_idx){
  return ((start_node_idx >= 0) && (start_node_idx < this->num_nodes_ -1) && (end_node_idx > start_node_idx) && (end_node_idx < this->num_nodes_)); 
}