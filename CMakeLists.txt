cmake_minimum_required(VERSION 2.8)
project(dijkstra_from_scratch)

set(CMAKE_CXX_STANDARD 11)

find_package(yaml-cpp REQUIRED)
find_package(Eigen3 3.3 REQUIRED)
find_package(Boost COMPONENTS program_options filesystem REQUIRED)

add_executable(run_dijkstra src/main.cpp)
target_link_libraries(run_dijkstra PRIVATE graph_utils yaml-cpp ${Boost_LIBRARIES})
target_include_directories(run_dijkstra PRIVATE ${Boost_INCLUDE_DIRS})

add_library(graph_utils src/graph_utils/graph_class.cpp src/graph_utils/graph_node.cpp src/graph_utils/my_dijkstra.cpp src/graph_utils/config_loader.cpp)
target_include_directories(graph_utils PUBLIC include/graph_utils)
target_link_libraries(graph_utils PRIVATE Eigen3::Eigen)