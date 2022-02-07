#pragma once
#include "directed_graph.h"


class Depth_First_Search{
    public:
    Depth_First_Search(Directed_Graph* graph);
    ~Depth_First_Search();

    std::vector<Path> depth_first_search_by_max_stops(const std::string& start_node, const std::string& end_node, unsigned int max_stops);
    std::vector<Path> depth_first_search_by_max_dist(const std::string& start_node,  const std::string& end_node, int max_dist);

    int get_num_paths_by_max_stops(const std::string& start_node, const std::string& end_node, unsigned int max_stops);
    int get_num_paths_by_equal_stops(const std::string& start_node, const std::string& end_node, unsigned int max_stops);
    int get_num_paths_by_max_dist(const std::string& start_node,  const std::string& end_node, int max_dist);

    private:
    void depth_first_search_by_max_stops_recursion(std::vector<Path>& paths, Path current_path, int current_node, int end_node, unsigned int stops_left);
    void depth_first_search_by_max_dist_recursion(std::vector<Path>& paths, Path current_path, int current_node, int end_node, int dist_left);

    Directed_Graph* graph;
};