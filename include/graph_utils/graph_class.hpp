#ifndef GRAPHCLASS
#define GRAPHCLASS

#include "graph_node.hpp"

#include <Eigen/Dense>
#include <memory>
#include <stddef.h>

class UndirectedGraph {
public:
  // constructors
  UndirectedGraph() = delete;
  UndirectedGraph(const size_t num_nodes, const double lower_weight,
                  const double upper_weight,
                  const double vertex_prob); // random initialization
  UndirectedGraph(
      const size_t num_nodes, const double lower_weight,
      const double upper_weight, const double vertex_prob,
      const std::string path_to_weights_file); // vertex initialization based on
                                               // given weights file

  // destructors
  ~UndirectedGraph() = default;

  // methods
  double get_shortest_path_costs() const;
  double get_avg_vertex_costs() const;
  void run_dijkstra();

private:
  void create_random_graph();
  void create_graph_based_on_file();
  void calculate_avg_vertex_weights();

  double lower_vertex_weight_;
  double upper_vertex_weight_;
  double vertex_prob_;
  double avg_vertex_cost_;
  double shortest_path_cost_;
  size_t num_nodes_;
  Eigen::MatrixXd
      vertex_weights_; // every row and column describes a node, the values
                       // within the matrix are the vertex weights
  std::vector<std::shared_ptr<GraphNode>> graph_nodes_;
};

#endif /* GRAPHCLASS */