#ifndef GRAPHCLASS
#define GRAPHCLASS

#include <stddef.h>
#include <Eigen/Dense>

class UndirectedGraph {
public:
    UndirectedGraph() = delete;
    UndirectedGraph(const size_t num_nodes, const double lower_weight, const double upper_weight, const double vertex_prob);  

private: 
    void create_random_graph(); 

    double lower_vertex_weight_; 
    double upper_vertex_weight_; 
    double vertex_prob_; 
    size_t num_nodes_; 
    Eigen::MatrixXd vertex_weights_; 

};

#endif /* GRAPHCLASS */