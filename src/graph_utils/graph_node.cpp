#include "graph_node.hpp"

#include <iostream>

GraphNode::GraphNode(const size_t num_graph_node,
                     const Eigen::VectorXd &weights_node_vertex) {
  // init node attributes
  this->num_node_ = num_graph_node;
  this->vertex_weights_ = weights_node_vertex;

  // calculate remaining node attributes
  Eigen::VectorXd::Index min_node_idx;
  this->min_vertex_weight_ = this->vertex_weights_.minCoeff(&min_node_idx);
  this->min_vertex_weight_idx_ = static_cast<size_t>(min_node_idx);
}

Eigen::VectorXd GraphNode::get_weights() const { return this->vertex_weights_; }

double GraphNode::get_min_vertex_weight() const {
  return this->min_vertex_weight_;
}

size_t GraphNode::get_min_vertex_node_idx() const {
  return this->min_vertex_weight_idx_;
}

size_t GraphNode::get_node_number() const { return this->num_node_; }

void GraphNode::print_vertex_weights() const {
  std::cout << "The vertex weights of node " << this->num_node_ << " are:\n"
            << this->vertex_weights_ << "\n";
}