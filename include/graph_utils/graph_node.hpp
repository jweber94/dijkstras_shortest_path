#ifndef GRAPH_NODE
#define GRAPH_NODE

#include <Eigen/Dense>
#include <memory>
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
  double get_last_cummulated_weight() const;
  size_t get_predecessor_node() const;
  void reset_cummulated_weight();
  void set_predecessor_node(const size_t &predecessor);
  void set_cummulated_weight(double current_weights_sum);

private:
  size_t num_node_; // index of the node within the graph
  Eigen::VectorXd vertex_weights_;
  double min_vertex_weight_;
  size_t min_vertex_weight_idx_;
  double last_cummulated_weight_;
  size_t predecessor_node_;
};

class CompGraphNode {
public:
  CompGraphNode() = default;

  int operator()(const std::shared_ptr<GraphNode> &node_1,
                 const std::shared_ptr<GraphNode> &node_2) {
    bool result = (node_1->get_last_cummulated_weight() >
                   node_2->get_last_cummulated_weight());
    return result;
  }
};

#endif /* GRAPH_NODE */