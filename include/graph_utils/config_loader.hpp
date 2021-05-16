#ifndef CONFIGLOADER
#define CONFIGLOADER

#include <string>

class ConfigLoader{
public: 
    ConfigLoader() = delete; 
    ConfigLoader(const std::string & input_path); 

    ~ConfigLoader() = default; 

    double get_lower_edge_weight() const;
    double get_upper_edge_weight() const;
    double get_edge_prob() const; 
    size_t get_num_nodes() const;  

private: 
    size_t num_nodes_;   
    double lower_;
    double upper_;
    double edge_prob_; 
};


#endif /* CONFIGLOADER */