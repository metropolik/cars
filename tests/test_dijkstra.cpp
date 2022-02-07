#include <vector>
#include <string>
#include "test_base.h"
#include "../src/directed_graph.h"
#include "../src/dijkstra.h"
#include <stdexcept>

bool test() {
    TEST_BEGIN("dijkstra");

    std::string graph_txt("AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7");
    Directed_Graph g(graph_txt); // exercise sheet

    Dijkstra dij(&g);
    // exercise sheet task 8
    ASSERT_EQUAL(dij.get_length_of_shortest_path("A", "C"), 9);

    // exercise sheet task 9
    ASSERT_EQUAL(dij.get_length_of_shortest_path("B", "B"), 9);
    

    std::string graph_txt2("AA1");
    Directed_Graph g2(graph_txt2);
    Dijkstra dij2(&g2);
    ASSERT_EQUAL(dij2.get_length_of_shortest_path("A", "A"), 1);
    EXPECT_EXCEPTION(dij2.get_length_of_shortest_path("A", "B"), std::invalid_argument);

    std::string graph_txt3("AA1, BB1, AB1, BA1");
    Directed_Graph g3(graph_txt3);
    Dijkstra dij3(&g3);
    ASSERT_EQUAL(dij3.get_length_of_shortest_path("A", "A"), 1);
    ASSERT_EQUAL(dij3.get_length_of_shortest_path("A", "B"), 1);
    ASSERT_EQUAL(dij3.get_length_of_shortest_path("B", "A"), 1);
    ASSERT_EQUAL(dij3.get_length_of_shortest_path("B", "B"), 1);

    std::string graph_txt4("AA1, BB1");
    Directed_Graph g4(graph_txt4);
    Dijkstra dij4(&g4);
    ASSERT_EQUAL(dij4.get_length_of_shortest_path("A", "A"), 1);
    ASSERT_EQUAL(dij4.get_length_of_shortest_path("B", "B"), 1);
    EXPECT_EXCEPTION(dij4.get_length_of_shortest_path("A", "B"), std::domain_error);
    EXPECT_EXCEPTION(dij4.get_length_of_shortest_path("B", "A"), std::domain_error);

    std::string graph_txt5("AB1");
    Directed_Graph g5(graph_txt5);
    Dijkstra dij5(&g5);
    ASSERT_EQUAL(dij5.get_length_of_shortest_path("A", "B"), 1);

    std::string graph_txt6("AB10, AC20, BD50, CD20, CE33, EF1, DF2, BE10, DE20");
    Directed_Graph g6(graph_txt6);
    Dijkstra dij6(&g6);
    ASSERT_EQUAL(dij6.get_length_of_shortest_path("A", "F"), 21);
    ASSERT_EQUAL(dij6.get_length_of_shortest_path("A", "C"), 20);
    ASSERT_EQUAL(dij6.get_length_of_shortest_path("A", "B"), 10);
    ASSERT_EQUAL(dij6.get_length_of_shortest_path("A", "E"), 20);
    ASSERT_EQUAL(dij6.get_length_of_shortest_path("A", "D"), 40);
    EXPECT_EXCEPTION(dij4.get_length_of_shortest_path("A", "A"), std::domain_error);

    TEST_END();
}

int main(int argc, char* argv[]) {
    bool t1 = test();
    return t1;
}
