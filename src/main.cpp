#include <iostream>
#include <string>
#include "graph_class.hpp"
#include "config_loader.hpp"


int main() {

    std::string config_path; 
    std::cout << "Plase insert the path to the configuration file:\n"; 
    //std::cin >> config_path; 
    config_path = "../etc/config.yml"; 

    try{
        
        ConfigLoader config_loader(config_path); 
        
        UndirectedGraph random_graph(config_loader.get_num_nodes(), config_loader.get_lower_edge_weight(), config_loader.get_upper_edge_weight(), config_loader.get_edge_prob()); 

        std::cout << "Calculation of Dijkstras Algorithm started\n";
        std::cout << config_path << "\n";
    
        std::cout << "Finished calculation.\n";
    }catch(...){
        std::cout << "Something went wrong! Is the path you handed in for the config.yml file valid? If yes, please contact the maintainer!\n";
    }      
    return 0; 
}