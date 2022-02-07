
add_executable( test_constructors test_constructors.cpp ../src/directed_graph.cpp ../src/command_processor.cpp ../src/dijkstra.cpp ../src/depth_first_search.cpp ../src/utils.cpp)
add_executable( test_path_dist test_path_dist.cpp ../src/directed_graph.cpp ../src/utils.cpp)
add_executable( test_depth_first_search test_depth_first_search.cpp ../src/directed_graph.cpp ../src/depth_first_search.cpp ../src/utils.cpp)
add_executable( test_dijkstra test_dijkstra.cpp ../src/directed_graph.cpp ../src/dijkstra.cpp ../src/utils.cpp)
add_executable( test_command_processor test_constructors.cpp ../src/directed_graph.cpp ../src/command_processor.cpp ../src/dijkstra.cpp ../src/depth_first_search.cpp ../src/utils.cpp)
add_executable( test_utils test_utils.cpp ../src/utils.cpp)

add_test( constructors test_constructors)
add_test( path_dist test_path_dist )
add_test( depth_first_search test_depth_first_search )
add_test( dijkstra test_dijkstra )
add_test( command_processor test_command_processor )
add_test( utils test_utils )