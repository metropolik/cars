#include <vector>
#include <string>
#include "test_base.h"
#include "../src/directed_graph.h"
#include <stdexcept>

bool test() {
    TEST_BEGIN("Path Traversal Distance");
    // exercise sheet graph
    std::string graph_txt("AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7");
    Directed_Graph g(graph_txt);

    // exercise sheet task 1
    std::vector<std::string> args;
    args.push_back("A");
    args.push_back("B");
    args.push_back("C");
    ASSERT_EQUAL(g.get_route_dist(args), 9);

    // exercise sheet task 2
    std::vector<std::string> args2;
    args2.push_back("A");
    args2.push_back("D");
    ASSERT_EQUAL(g.get_route_dist(args2), 5);

    // exercise sheet task 3
    std::vector<std::string> args3;
    args3.push_back("A");
    args3.push_back("D");
    args3.push_back("C");
    ASSERT_EQUAL(g.get_route_dist(args3), 13);

    // exercise sheet task 4
    std::vector<std::string> args4;
    args4.push_back("A");
    args4.push_back("E");
    args4.push_back("B");
    args4.push_back("C");
    args4.push_back("D");
    ASSERT_EQUAL(g.get_route_dist(args4), 22);

    // exercise sheet task 5
    std::vector<std::string> args5;
    args5.push_back("A");
    args5.push_back("E");
    args5.push_back("D");
    EXPECT_EXCEPTION(g.get_route_dist(args5), std::domain_error); // NO ROUTE


    // additional tests
    std::vector<std::string> args6;
    args6.push_back("A");
    args6.push_back("D");
    EXPECT_EXCEPTION(g.get_route_dist(args6), std::domain_error); // NO ROUTE

    std::vector<std::string> args7;
    args7.push_back("E");
    EXPECT_EXCEPTION(g.get_route_dist(args7), std::invalid_argument); // NOT ENOUGH NODES

    std::vector<std::string> args8;
    args8.push_back("C");
    args8.push_back("E");
    args8.push_back("B");
    args8.push_back("C");
    args8.push_back("E");
    args8.push_back("B");
    args8.push_back("C");
    ASSERT_EQUAL(g.get_route_dist(args8), 18);


    std::string graph_txt2("AZ11");
    Directed_Graph g2(graph_txt2);

    std::vector<std::string> args9;
    args9.push_back("C");
    args9.push_back("Z");
    EXPECT_EXCEPTION(g2.get_route_dist(args9), std::invalid_argument); // node does not exist

    std::vector<std::string> args10;
    args10.push_back("A");
    args10.push_back("Z");
    ASSERT_EQUAL(g2.get_route_dist(args10), 11);

    TEST_END();
}

int main(int argc, char* argv[]) {
    bool t1 = test();
    return t1;
}
