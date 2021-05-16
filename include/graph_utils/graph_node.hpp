#ifndef GRAPHNODE
#define GRAPHNODE

#include "graph_vertex.hpp"

#include <stddef.h>
#include <vector>
#include <tuple>
#include <map>
#include <memory>

class GraphNode {
public:
    GraphNode() = default; 
    GraphNode(const size_t neighbours, const size_t node_idx, const std::vector<std::tuple<size_t, double>> neighbour_idx_weight);


private: 
    size_t node_idx_;
    std::map<size_t, std::shared_ptr<GraphVertex>> vertex_reference_;    
};

#endif /* GRAPHNODE */