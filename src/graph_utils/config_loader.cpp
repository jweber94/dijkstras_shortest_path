#include "config_loader.hpp"

#include <yaml-cpp/yaml.h>

ConfigLoader::ConfigLoader(const std::string &input_path) {
  YAML::Node yaml_reader = YAML::LoadFile(input_path);

  this->num_nodes_ = yaml_reader["num_nodes"].as<size_t>();
  this->lower_ = yaml_reader["min_weight_edge"].as<double>();
  this->upper_ = yaml_reader["max_weight_edge"].as<double>();
  this->edge_prob_ = yaml_reader["edge_prob_thresh"].as<double>();
}

// Test functiontions DONE
double ConfigLoader::get_lower_edge_weight() const { return this->lower_; }

double ConfigLoader::get_upper_edge_weight() const { return this->upper_; }

double ConfigLoader::get_edge_prob() const { return this->edge_prob_; }

size_t ConfigLoader::get_num_nodes() const { return this->num_nodes_; }