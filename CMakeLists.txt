cmake_minimum_required(VERSION 3.10)

project(Cars)

# add the executable
add_executable(Cars src/main.cpp src/command_processor.cpp src/directed_graph.cpp src/utils.cpp src/depth_first_search.cpp src/dijkstra.cpp)

ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)

