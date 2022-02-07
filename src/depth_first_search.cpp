#include "depth_first_search.h"
#include <stdexcept>
#include <iostream>

Depth_First_Search::Depth_First_Search(Directed_Graph* graph) {
    if (graph == nullptr) {
        throw std::invalid_argument("Given graph does not exist!");
    } 
    this->graph = graph;
}

Depth_First_Search::~Depth_First_Search() {
    
}

std::vector<Path> Depth_First_Search::depth_first_search_by_max_stops(const std::string& start_node, const std::string& end_node, unsigned int max_stops) {
    // check if nodes even exist
    if (!graph->node_name_exists(start_node) || !graph->node_name_exists(end_node)) {
        throw std::invalid_argument("One or both nodes don't exist");
    }
    // translate node names to ids
    int start_node_id = graph->node_name_to_id(start_node);
    int end_node_id = graph->node_name_to_id(end_node);

    // this vector is the output of the recursion operation, passed via reference
    std::vector<Path> paths;

    depth_first_search_by_max_stops_recursion(paths, Path(), start_node_id, end_node_id, max_stops + 1);

    return paths;
}

std::vector<Path> Depth_First_Search::depth_first_search_by_max_dist(const std::string& start_node, const std::string& end_node, int max_dist) {
    // check if nodes even exist
    if (!graph->node_name_exists(start_node) || !graph->node_name_exists(end_node)) {
        throw std::invalid_argument("One or both nodes don't exist!");
    }
    // max dist needs to be signed so that the recursion algorithm does not underflow
    if (max_dist < 1) {
        throw std::invalid_argument("Max dist cannot be smaller than 1!");
    }
    // translate node names to ids
    int start_node_id = graph->node_name_to_id(start_node);
    int end_node_id = graph->node_name_to_id(end_node);

    // this vector is the output of the recursion operation, passed via reference
    std::vector<Path> paths;

    depth_first_search_by_max_dist_recursion(paths, Path(), start_node_id, end_node_id, max_dist);

    return paths;
}

void Depth_First_Search::depth_first_search_by_max_stops_recursion(std::vector<Path>& paths, Path current_path, int current_node, int end_node, unsigned int stops_left) {
    // stop recursion if we reach max recursion depth
    if (stops_left == 0) { return; }

    // update the current_path
    current_path.push_back(current_node);

    // we found the end_node, so we append the current path to the possible paths
    // we do not terminate the recursion as cycles even through the end node
    // are allowed
    if (current_node == end_node) {
        paths.push_back(current_path);
    }

    // each node has a list for its outgoing edges
    // for nodes without any this list is empy
    for (auto recv_edge : graph->get_outgoing_edges_of_node(current_node)) {
        depth_first_search_by_max_stops_recursion(paths, current_path, recv_edge.end_node, end_node, stops_left - 1);
    }
}

void Depth_First_Search::depth_first_search_by_max_dist_recursion(std::vector<Path>& paths, Path current_path, int current_node, int end_node, int dist_left) {
    // stop recursion if we reach max recursion depth
    if (dist_left <= 0) { return; }

    // update the current_path
    current_path.push_back(current_node);

    // we found the end_node, so we append the current path to the possible paths
    // we do not terminate the recursion as cycles even through the end node
    // are allowed
    if (current_node == end_node) {
        paths.push_back(current_path);
    }

    // each node has a list for its outgoing edges
    // for nodes without any this list is empy
    for (auto recv_edge : graph->get_outgoing_edges_of_node(current_node)) {
        depth_first_search_by_max_dist_recursion(paths, current_path, recv_edge.end_node, end_node, dist_left - recv_edge.weight);
    }
    
}

int Depth_First_Search::get_num_paths_by_max_stops(const std::string& start_node, const std::string& end_node, unsigned int max_stops) {
    std::vector<Path> paths = depth_first_search_by_max_stops(start_node, end_node, max_stops);

    // we have the resulting paths but we still need to filter out paths with length 0 i.e. C->C
    int number_valid_paths = 0;
    for (Path path : paths) {
        if (path.size() > 1) {
            number_valid_paths++;
        }
    }

    return number_valid_paths;
}

int Depth_First_Search::get_num_paths_by_equal_stops(const std::string& start_node, const std::string& end_node, unsigned int max_stops) {
    std::vector<Path> paths = depth_first_search_by_max_stops(start_node, end_node, max_stops);

    // we have the resulting paths but we still need to filter out paths which don't have exactly the
    // desired number of stops
    int number_valid_paths = 0;
    for (Path path : paths) {
        if (path.size() == (max_stops + 1)) {
            number_valid_paths++;
        }
    }

    return number_valid_paths;
}

int Depth_First_Search::get_num_paths_by_max_dist(const std::string& start_node, const std::string& end_node, int max_dist) {
    std::vector<Path> paths = depth_first_search_by_max_dist(start_node, end_node, max_dist);

    // we have the resulting paths but we still need to filter out paths which have a distance of 0
    // i.e. C->C
    int number_valid_paths = 0;
    for (Path path : paths) {
        if (path.size() > 1) {
            number_valid_paths++;
        }
    }

    return number_valid_paths;
}
