#include "config_loader.hpp"
#include "graph_class.hpp"
#include "graph_node.hpp"
#include <Eigen/Dense>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  // command line parser
  boost::program_options::options_description desc{
      "Options for the calculation of dijkstras shortest path algorithm"};
  boost::program_options::variables_map vm;
  std::string config_path = "none";

  try {
    desc.add_options()(
        "help,h", "Help and overview of all possible command line options")(
        "path,p",
        boost::program_options::value<std::string>()->default_value(
            "../etc/config.yml"),
        "Path to the configuration file");

    boost::program_options::store(
        boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

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
  } catch (const boost::program_options::error &ex) {
    std::cerr << ex.what() << "\n";
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
    random_graph.find_path(config_loader.get_start_node_idx(),
                           config_loader.get_finish_node_idx());

    random_graph.print_shortest_path_idxs();
    std::cout << "Finished program.\n";

  } catch (...) {

    std::cout
        << "Something went wrong! Is the path you handed in for the config.yml "
           "file valid? If yes, please contact the maintainer!\n";
  }
  return 0;
}