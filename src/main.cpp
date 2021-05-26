#include "config_loader.hpp"
#include "graph_class.hpp"
#include "graph_node.hpp"
#include <Eigen/Dense>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  /*
  // DEBUG
  Eigen::VectorXd test_vec(3);
  test_vec << 2.1, 1.1, 5.5;
  GraphNode test_node(2, test_vec);
  test_node.get_weights();
  std::cout << "min idx: " << test_node.get_min_vertex_node_idx() << "\n";
  std::cout << "min weight val: " << test_node.get_min_vertex_weight() << "\n";
  test_node.print_vertex_weights();
  // DEBUG END
  */

  // command line parser
  boost::program_options::options_description desc{"Options"};
  boost::program_options::variables_map vm;
  std::string config_path = "none";

  desc.add_options()("help,h",
                     "Help and overview of all possible command line options")(
      "path,p",
      boost::program_options::value<std::string>()->default_value(
          "../etc/config.yml"),
      "Path to the configuration file");

  boost::program_options::store(
      boost::program_options::parse_command_line(argc, argv, desc), vm);

  config_path = vm["path"].as<std::string>();

  if (vm.count("help")) {
    std::cout << desc << "\n";
    exit(0);
  }
  if ((config_path == "none") || !(boost::filesystem::exists(config_path))) {
    std::cerr << "The path to the config is not valid. Please check your "
                 "config path after --path /path/to/your/config.yml\n";
    exit(0);
  }

  // calculation
  try {
    // create objects for the calculation
    ConfigLoader config_loader(config_path);
    UndirectedGraph random_graph(
        config_loader.get_num_nodes(), config_loader.get_lower_edge_weight(),
        config_loader.get_upper_edge_weight(), config_loader.get_edge_prob(),
        config_loader.get_num_trials());

    random_graph.print_weight_matrix();
    std::cout << "The average vertex costs are: "
              << random_graph.get_avg_vertex_costs() << "\n";

    std::cout << "Calculation of Dijkstras Algorithm started\n";
    random_graph.run_dijkstra();

    random_graph.print_shortest_path_idxs();
    std::cout << "Finished program.\n";

  } catch (...) {

    std::cout
        << "Something went wrong! Is the path you handed in for the config.yml "
           "file valid? If yes, please contact the maintainer!\n";
  }
  return 0;
}