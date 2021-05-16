#include "graph_class.hpp"

#include <iostream>

UndirectedGraph::UndirectedGraph(const size_t num_nodes, const double lower_weight, const double upper_weight, const double vertex_prob) {
    // get the run parameter
    this->lower_vertex_weight_ = lower_weight;
    this->upper_vertex_weight_ = upper_weight; 
    this->vertex_prob_ = vertex_prob; 
    this->num_nodes_ = num_nodes; 

    // preallocation    
    this->vertex_weights_ = -(Eigen::MatrixXd::Identity(this->num_nodes_, this->num_nodes_)); 

    // initialize random graph
    std::cout << "The vertex_weight_ matrix has the size: " << this->vertex_weights_.rows() << "x" << this->vertex_weights_.cols() << "\n"; 
    std::cout << "This is the matrix:\n" << this->vertex_weights_ << "\n"; 
    
    this->create_random_graph(); 
}

void UndirectedGraph::create_random_graph() {
    std::cout << "Creating random graph\n"; 
}