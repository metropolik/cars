#include "dijkstra.h"
#include <stdexcept>
#include <iostream>
#include <queue>
#include <utility>
#include <limits>
#include <unordered_set>
#include <algorithm>


// this node type specifically exists to use the priority queue
// the first int is the distance to the start node, it is only used while stored in the queue
typedef std::pair<int, int> QNode;

struct min_heap_compare {
    constexpr bool operator()(QNode const& a, QNode const& b) const noexcept {
            return a.first > b.first;
        }
};

Dijkstra::Dijkstra(Directed_Graph* graph) {
    if (graph == nullptr) {
        throw std::invalid_argument("Given graph does not exist!");
    } 
    this->graph = graph;
}

Dijkstra::~Dijkstra() {
    
}

std::pair<Path, int> Dijkstra::shortest_path(const std::string& start_node, const std::string& end_node) {
    if (!graph->node_name_exists(start_node) || !graph->node_name_exists(end_node)) {
        throw std::invalid_argument("One or both nodes dont't exist in the graph!");
    }
    int start_node_id = graph->node_name_to_id(start_node);
    int end_node_id = graph->node_name_to_id(end_node);

    // create all required data structures for dijkstra
    std::priority_queue<QNode, std::vector<QNode>, min_heap_compare> minq;
    std::map<int, int> dist;
    // parent needs to be int so we can have a special value for not assigned parent
    std::map<int, int> parent; 
    std::unordered_set<int> visited;
    std::vector<int> all_nodes = graph->get_all_nodes();
    int max_int = std::numeric_limits<int>::max();

    for (auto node : all_nodes) {
        parent[node] = -1;
        dist[node] = max_int;
    }

    // we skip the very first step of dijkstra 
    for (auto recv_edge : graph->get_outgoing_edges_of_node(start_node_id)) {
        int neighbor = recv_edge.end_node;
        int direct_dist_to_neighbor = recv_edge.weight;
        QNode new_qnode = {direct_dist_to_neighbor, neighbor};
        minq.push(new_qnode);
        dist[neighbor] = direct_dist_to_neighbor;
        parent[neighbor] = start_node_id;
    }

    while (!minq.empty()) {
        QNode qnode = minq.top();
        int node = qnode.second;
        minq.pop();
        visited.insert(node);

        // we processed the end node and therefore found the
        // shortest path
        if (node == end_node_id) {
            break;
        }
        for (auto recv_edge : graph->get_outgoing_edges_of_node(node)) {
            int neighbor = recv_edge.end_node;
            if (visited.find(neighbor) == visited.end()) {
                int old_dist_to_start = dist[neighbor];
                int new_dist_to_start = qnode.first + recv_edge.weight;
                if (new_dist_to_start < old_dist_to_start) {
                    QNode new_qnode = {new_dist_to_start, neighbor};
                    minq.push(new_qnode);
                    dist[neighbor] = new_dist_to_start;
                    parent[neighbor] = node;
                }
            }
        }
    }

    // extract path
    Path path;
    // if the end node was never reached but all nodes were processed
    // there is no route
    if (visited.find(end_node_id) == visited.end()) {
        throw std::domain_error("No route between start and end exists!");
    }

    int current_node = end_node_id;
    // because we start at the end_node, back-track to the start_node
    // and the end_node was visited, it is guranteed that each parent
    // in the shortest path is set correctly
    while ((current_node != start_node_id) || path.size() == 0) {
        path.push_back(current_node);
        current_node = parent[current_node];
    }
    path.push_back(start_node_id);

    std::reverse(path.begin(), path.end());

    return std::make_pair(path, dist[end_node_id]); 
}

int Dijkstra::get_length_of_shortest_path(const std::string& start_node, const std::string& end_node) {
    std::pair<Path, int> shortest_path_dist;
    shortest_path_dist = shortest_path(start_node, end_node);

    return shortest_path_dist.second;
}
