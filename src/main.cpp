#include "config_loader.hpp"
#include "graph_class.hpp"
#include "graph_node.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <string>

int main() {

  std::string config_path;
  std::cout << "Plase insert the path to the configuration file:\n";
  // std::cin >> config_path;
  config_path = "../etc/config.yml"; // debug

  // debug
  Eigen::VectorXd test_vec(3);
  test_vec << 2.1, 1.1, 5.5;
  GraphNode test_node(2, test_vec);
  test_node.get_weights();
  std::cout << "min idx: " << test_node.get_min_vertex_node_idx() << "\n";
  std::cout << "min weight val: " << test_node.get_min_vertex_weight() << "\n";

  // debug end

  try {

    ConfigLoader config_loader(config_path);

    UndirectedGraph random_graph(
        config_loader.get_num_nodes(), config_loader.get_lower_edge_weight(),
        config_loader.get_upper_edge_weight(), config_loader.get_edge_prob());

    std::cout << "the average vertex costs are: "
              << random_graph.get_avg_vertex_costs() << "\n";

    std::cout << "Calculation of Dijkstras Algorithm started\n";
    std::cout << config_path << "\n";

    std::cout << "Finished calculation.\n";
  } catch (...) {
    std::cout
        << "Something went wrong! Is the path you handed in for the config.yml "
           "file valid? If yes, please contact the maintainer!\n";
  }
  return 0;
}