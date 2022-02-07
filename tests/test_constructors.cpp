#include <vector>
#include <string>
#include "test_base.h"
#include "../src/directed_graph.h"
#include "../src/command_processor.h"
#include "../src/depth_first_search.h"
#include "../src/dijkstra.h"
#include <stdexcept>

bool test() {
    TEST_BEGIN("Constructor Test");

    // Directed Graph
    // exercise sheet graph
    std::string graph_txt("AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7");
    try {
        Directed_Graph g(graph_txt); // exercise sheet
    } catch(...) {
        ASSERT_TRUE(0);
    }

    std::string graph_text2("AA3, AA3"); // legal
    try {
        Directed_Graph g2(graph_text2);
    } catch(...) {
        ASSERT_TRUE(0);
    }

    std::string graph_text23("AB1");
    Directed_Graph g23(graph_text23);
    ASSERT_EQUAL(g23.get_all_nodes().size(), 2)

    // adding the same edge twice is allowed but only the first is used
    // the second one is silently ignored
    std::string graph_text24("AB1, AB2");
    Directed_Graph g24(graph_text24);
    ASSERT_EQUAL(g24.get_outgoing_edges_of_node(g24.node_name_to_id("A")).size(), 1)

    std::string graph_text3("A22, AB3"); // illegal
    EXPECT_EXCEPTION(Directed_Graph(graph_text3), std::invalid_argument); 

    std::string graph_text4("AAA"); // illegal
    EXPECT_EXCEPTION(Directed_Graph(graph_text4), std::invalid_argument); 

    std::string graph_text5("999"); // illegal
    EXPECT_EXCEPTION(Directed_Graph(graph_text5), std::invalid_argument); 

    std::string graph_text6(""); // empty graph is legal
    Directed_Graph g3(graph_text6);
    ASSERT_EQUAL(g3.get_all_nodes().size(), 0);

    // general creation of instances
    // command processor
    try {
        Command_Processor cp;
    } catch(...) {
        ASSERT_TRUE(0);
    }

    // dijkstra
    Directed_Graph g(graph_txt);
    try {
        Dijkstra dij(&g);
    } catch(...) {
        ASSERT_TRUE(0);
    }

    EXPECT_EXCEPTION(Dijkstra(nullptr), std::invalid_argument);

    // depth first search
    try {
        Depth_First_Search dfs(&g);
    } catch(...) {
        ASSERT_TRUE(0);
    }

    EXPECT_EXCEPTION(Depth_First_Search(nullptr), std::invalid_argument);

    TEST_END();
}

int main(int argc, char* argv[]) {
    bool t1 = test();
    return t1;
}
