# Project: Dijkstra's shortest path algorithm

This project contains my own implementation of dijkstras shortest path algorithm (https://de.wikipedia.org/wiki/Dijkstra-Algorithmus) from scratch. It is realized by using a graph data structore (in contrast to a matrix representation). The advantage of the graph implementation is, that it is more memory and computational efficient then the matrix representation if the nodes within the graph are sparsely connected. In the first version, a random graph is generated and dijkstras algorithm is applied to it to find the shortest path from a start node index to the end node index. The start and end node are given in the config.yml in ```/etc```. 
Currently, the program creates a random graph and checks, if the graph is fully connected. If not, a new random graph will be generated until a completly connected graph is generated. (or the maximum number of trials are exceeded - currently 10) 
After a valid graph is generated, dijkstras algorithm will be applied to it and the shortest path with it's cost is printed to the console.    

## CAUTION: Not finished yet! ToDos:

- [x] Finalize the Dockerfile and Readme in first version
- [ ] Find the bug in dijkstras algorithm: Sometimes there is an index error and sometimes a memory access error!
    - Try the algorithm until the error case is generated -> save the graph configuration, hard-code it in the graph constructor class temporarily and debug throu the program
    - Error-Cases: "Something went wrong" (during traversing) & "Segmentation fault" (especially if the graph is very sparse)
- [ ] Think about and implement a visualization of the graph with its shortest path from start to finish (probably in python)
- [ ] Load a given graph from a csv file and calculate the shortest path 
- [ ] Implement Minimum Spanning Tree Algorithm

## Usage

The following instructions are described for Linux/MacOS. They can also be transferred to Windows with a few adjustments.

Open up a terminal and clone the code to your local machine  

    $ git clone https://github.com/jweber94/dijkstras_shortest_path.git

Then, go into the cloned folder

    $ cd dijkstras_shortest_path

To make the code run on all machines/OS, I created a _Dockerfile_ for building a Docker Image/Container to run the code within an Ubuntu 18.04 emulation.
In order to make it run, you have to build the docker (this might take a while, depending on your internet connection and hardware):

    $ docker build -t proj:dijkstra .

Then you can start the docker container with a terminal:

    $ docker run -it --name dijkstra_container  proj:dijkstra /bin/bash

To go into the container with a second terminal, you can use:

    $ docker exec -it dijkstra_container /bin/bash

Now you are in the docker within the repository folder and able to run the code. In ```/dijkstra_dir/my_code/build``` you can find the _run_dijkstra_ executable. 
Go into the folder and start the executable with 

    # cd ./build
    # ./run_dijkstra

You can execute it and hand it a configuration file with the ```--path /path/to/your/config.yml```. You can find a reference for the structure in the folder ```/etc```, eg. ```--path ../etc/config.yml```) Then the execution will start and the results will be printed to the terminal. 

## Explaination of the configuration file

+ ```num_nodes```: Number of nodes within the randomly generated graph
+ ```edge_prob_thresh```: Probability that an edge between two nodes will be accepted during the random graph generation
+ ```min_weight_edge```: Minimum weight of an edge between two nodes within the randomly generated graph
+ ```max_weight_edge```: Maximum weight of an edge between two nodes within the randomly generated graph
+ ```num_random_trials```: Number of trials for generating a fully connected random graph. After this number of trials, the program execution will be terminated
+ ```start_idx```: Start node-index for dijkstras shortest path search
+ ```finish_idx```: End node-index for dijkstras shortest path search - The highest index you can choose is 1 - ```num_nodes```, since the first node in the graph get the index 0. 

## Requirements

The project is meant to be docker based. You can see the requirements to run it on your local machine in the Dockerfile. It should be possible with a Ubuntu 18.04 LTS installation with yaml-cpp, libboost-all-dev and Eigen3 installed. 