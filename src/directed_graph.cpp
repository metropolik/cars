#include "directed_graph.h"
#include <stdexcept>
#include <iostream>

Directed_Graph::Directed_Graph(const std::string& graph_text) 
    : next_new_node_id(0)    
{
    parse_graph_text(graph_text);
}

Directed_Graph::~Directed_Graph() {
}

int Directed_Graph::node_name_to_id(std::string name) {
    if (node_name_exists(name)) {
        return node_id_map[name];
    } else {
        throw std::invalid_argument("Node does not exist!");
    }
}

// if the node already exists it returns the current id
// if it does not it creates a new entry and returns that id
int Directed_Graph::create_if_new_node(std::string name) {
    if (node_name_exists(name)) {
        return node_id_map[name];
    } else {
        // create a new name entry in node_id_map
        node_id_map[name] = next_new_node_id;
        int this_nodes_id = next_new_node_id;
        next_new_node_id++;

        // add node to ajacency list
        if (graph_adjacency.find(this_nodes_id) == graph_adjacency.end()) {
            graph_adjacency[this_nodes_id] = std::vector<Receiving_Node_Edge>();
        }

        return this_nodes_id;
    }
}

int Directed_Graph::query_edge(int start_node, int end_node) {
    if (!node_id_exists(start_node) || !node_id_exists(end_node)) {
        throw std::invalid_argument("One or both nodes do not exist!");
    }
    auto& outgoing_edges_of_start_node = graph_adjacency[start_node];
    for (auto& edge : outgoing_edges_of_start_node) {
        if (edge.end_node == end_node) {
            return edge.weight;
        }
    }
    throw std::domain_error("Edge between start and end" 
                                    " node does not exist!");
}

int Directed_Graph::get_route_dist(std::vector<std::string> nodes) {
    int dist_sum = 0;
    if (nodes.size() < 2) {
        std::string errmsg = std::string("Not enough nodes to calculate a route! Only ");
        errmsg += std::to_string(nodes.size()) + std::string(" were given!");
        throw std::invalid_argument(errmsg);
    }
    for (int i = 0; i < nodes.size() - 1; i++) {
        int start_node = node_name_to_id(nodes[i]);
        int end_node = node_name_to_id(nodes[i+1]);
        dist_sum += query_edge(start_node, end_node);
    }
    return dist_sum;
}

std::string Directed_Graph::node_id_to_name(int node_id) {
    // unforuntately Cpp does not have a bidirectional map
    // however the names are for the tasks of this exercise not
    // required. They would, however, come in handy for debugging
    // so we do a linear search through the map in case we need them

    for (auto iterator = node_id_map.begin(); iterator != node_id_map.end(); iterator++) {
        if (iterator->second == node_id) {
            return iterator->first;
        }
    }
    // the node id does not exist, so throw an exception
    std::string errmsg;
    errmsg += std::string("Node id does not exist! ") + std::to_string(node_id);
    throw std::invalid_argument(errmsg);
}

void Directed_Graph::parse_graph_text(const std::string& graph_text) {
    auto edges_strings = split_string_by(graph_text, std::string(", "));

    // currently each node is a single letter
    // however, if this changes later, only this method needs to be
    // adapted and a different splitting method implemented
    for (auto edge : edges_strings) {
        // check for valid format
        // first two characters of edge string need to be alphabet chars
        if (!std::isalpha(edge[0]) || !std::isalpha(edge[1])) {
            std::string errmsg = std::string("The names of the nodes of the edge \"") + edge + std::string("\" are not alphabet characters!");
            throw std::invalid_argument(errmsg);
        }
        // everything afterwards is the weight of the edge i.e. a number
        // stoi will throw std::invalid_argument if this is not the case
        int weight = std::stoi(edge.substr(2, edge.length() - 1));
        if (weight <= 0) {
            std::string errmsg = std::string("Edge weights cannot be 0 or negative!");
            throw std::invalid_argument(errmsg);
        }

        // map node names to ids
        int start_node = create_if_new_node(edge.substr(0, 1));
        int end_node = create_if_new_node(edge.substr(1, 1));

        // create edge
        add_edge(start_node, end_node, weight);
    }
}

void Directed_Graph::add_edge(int start_node, int end_node, int weight) {
    // validate that these nodes actually exist
    if (!node_id_exists(start_node) || !node_id_exists(end_node)) {
        throw std::invalid_argument("ERROR: Tried to create a edge between" 
                                        " one or more nodes that don't exist!");
    }

    // if the same edge is added multiple times, only the first counts
    if (edge_exists(start_node, end_node)) {
        return; 
    }

    // as all nodes are created with create_if_new_node
    // we can be sure that an empty vector has also been added to graph_adjacency
    graph_adjacency[start_node].push_back({end_node, weight});
    
}

bool Directed_Graph::node_id_exists(int id) {
    return id < next_new_node_id;
}

bool Directed_Graph::node_has_outgoing_edges(int node_id) {
    return graph_adjacency[node_id].size() > 0; 
}

bool Directed_Graph::node_name_exists(std::string name) {
    return node_id_map.find(name) != node_id_map.end();
}

std::vector<Receiving_Node_Edge> Directed_Graph::get_outgoing_edges_of_node(int node_id) {
    return graph_adjacency[node_id];
}

// we don't keep an active list for this to make data consistency easier
std::vector<int> Directed_Graph::get_all_nodes() {
    std::vector<int> nodes;
    for (auto iterator = graph_adjacency.begin(); iterator != graph_adjacency.end(); iterator++) {
        nodes.push_back(iterator->first);
    }
    return nodes;
}

bool Directed_Graph::edge_exists(int start_node_id, int end_node_id) {
    if (!node_id_exists(start_node_id) || !node_id_exists(end_node_id)) {
        throw std::invalid_argument("One or both nodes do not exist!");
    }
    auto& outgoing_edges_of_start_node_id = graph_adjacency[start_node_id];
    for (auto& edge : outgoing_edges_of_start_node_id) {
        if (edge.end_node == end_node_id) {
            return true;
        }
    }
    return false;
}
