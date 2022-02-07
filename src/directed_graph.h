#pragma once
#include <string>
#include <map>
#include <vector>
#include "utils.h"

// This struct represents an edge
// the origin/ of this edge is stored 
// via the graph_adjacency map
struct Receiving_Node_Edge {
    int end_node;
    int weight;
};

class Directed_Graph {
    public:
        Directed_Graph(const std::string& graph_text);
        ~Directed_Graph();

        int query_edge(int start_node, int end_node);
        int get_route_dist(std::vector<std::string> nodes);

        bool edge_exists(int start_node_id, int end_node_id);
        bool node_name_exists(std::string name);
        bool node_id_exists(int id);

        int node_name_to_id(std::string name);
        std::string node_id_to_name(int node_id);

        bool node_has_outgoing_edges(int node_id);
        std::vector<Receiving_Node_Edge> get_outgoing_edges_of_node(int node_id);
        std::vector<int> get_all_nodes();

    private:
        void parse_graph_text(const std::string& graph_text);
        void add_edge(int start_node, int end_node, int weight);
        int create_if_new_node(std::string name);

        // to be more efficient, we do not use the string names
        // of the nodes when processing but instead remap them
        // to ids of type int
        std::map<std::string, int> node_id_map;
        std::map<int, std::vector<Receiving_Node_Edge>> graph_adjacency;

        // for mapping the node names to numbers we need a counter
        // to know which id the next new node gets
        int next_new_node_id;
};