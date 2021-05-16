#ifndef GRAPHNODE
#define GRAPHNODE

#include "graph_vertex.hpp"

#include <Eigen/Dense>
#include <stddef.h>

class GraphNode {
public:
  // constructors
  GraphNode() = delete;
  GraphNode(const size_t num_graph_node,
            const Eigen::VectorXd &weights_node_vertex);

  // destructors
  ~GraphNode() = default;

  // member
  Eigen::VectorXd get_weights() const;
  double get_min_vertex_weight() const;
  size_t get_min_vertex_node_idx() const;
  size_t get_node_number() const;

private:
  size_t num_node_; // index of the node within the graph
  Eigen::VectorXd vertex_weights_;
  double min_vertex_weight_;
  size_t min_vertex_weight_idx_;
};

#endif /* GRAPHNODE */