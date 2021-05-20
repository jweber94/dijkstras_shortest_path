#ifndef GRAPH_NODE
#define GRAPH_NODE

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
  void print_vertex_weights() const;

private:
  size_t num_node_; // index of the node within the graph
  Eigen::VectorXd vertex_weights_;
  double min_vertex_weight_;
  size_t min_vertex_weight_idx_;
};

class CompGraphNode {
public:
  CompGraphNode() = default;

  int operator()(const GraphNode &node_1, const GraphNode &node_2) {
    bool result = true;
    // ToDo: create comparison function for the node order to create a min_heap
    return result;
  }
};

#endif /* GRAPH_NODE */