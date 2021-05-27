#include "config_loader.hpp"

#include <yaml-cpp/yaml.h>

ConfigLoader::ConfigLoader(const std::string &input_path) {
  YAML::Node yaml_reader = YAML::LoadFile(input_path);

  this->num_nodes_ = yaml_reader["num_nodes"].as<size_t>();
  this->num_trials_ = yaml_reader["num_random_trials"].as<size_t>();
  this->lower_ = yaml_reader["min_weight_edge"].as<double>();
  this->upper_ = yaml_reader["max_weight_edge"].as<double>();
  this->edge_prob_ = yaml_reader["edge_prob_thresh"].as<double>();
  this->start_idx_ = yaml_reader["start_idx"].as<int>();
  this->finish_idx_ = yaml_reader["finish_idx"].as<int>();
}

// Test functiontions DONE
double ConfigLoader::get_lower_edge_weight() const { return this->lower_; }

double ConfigLoader::get_upper_edge_weight() const { return this->upper_; }

double ConfigLoader::get_edge_prob() const { return this->edge_prob_; }

size_t ConfigLoader::get_num_nodes() const { return this->num_nodes_; }

size_t ConfigLoader::get_num_trials() const { return this->num_trials_; }

int ConfigLoader::get_start_node_idx() const { return this->start_idx_; }

int ConfigLoader::get_finish_node_idx() const { return this->finish_idx_; }