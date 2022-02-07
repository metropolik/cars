#pragma once
#include "directed_graph.h"


class Dijkstra {
    public:
    Dijkstra(Directed_Graph* graph);
    ~Dijkstra();

    std::pair<Path, int> shortest_path(const std::string& start_node, const std::string& end_node);
    int get_length_of_shortest_path(const std::string& start_node, const std::string& end_node);

    private:
    Directed_Graph* graph;
};