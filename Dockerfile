FROM ubuntu:18.04
ENV name="dijkstra_shortest_path"

RUN apt-get update && \
    apt-get install -y vim \
    git cmake build-essential \
    python3-pip tmux \
    clang-tidy eog \
    libboost-all-dev \ 
    wget

WORKDIR /dijkstra_dir

# install yaml-cpp
RUN git clone https://github.com/jbeder/yaml-cpp.git
WORKDIR /dijkstra_dir/yaml-cpp/build
RUN cmake -DYAML_BUILD_SHARED_LIBS=ON ..
RUN make -j12
RUN make install

# install Eigen3
WORKDIR /dijkstra_dir/eigen3 
RUN wget https://gitlab.com/libeigen/eigen/-/archive/3.3.9/eigen-3.3.9.tar.bz2
RUN tar xjf eigen-3.3.9.tar.bz2
WORKDIR /dijkstra_dir/eigen3/eigen-3.3.9
RUN mkdir build
WORKDIR /dijkstra_dir/eigen3/eigen-3.3.9/build
RUN cmake .. && make install -j12

#  copy the code from the repo into the container
WORKDIR /dijkstra_dir/my_code
COPY . /dijkstra_dir/my_code/
WORKDIR /dijkstra_dir/my_code/build
RUN rm -rf *
RUN cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
RUN make -j12

# install the neccessary python packages
RUN pip3 install numpy && pip3 install matplotlib==3.1.1 && pip3 install pep8

# go to the repo-folder in the container
WORKDIR /dijkstra_dir/my_code