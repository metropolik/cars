#include <vector>
#include <string>
#include "test_base.h"
#include "../src/directed_graph.h"
#include "../src/depth_first_search.h"
#include <stdexcept>

bool test() {
    TEST_BEGIN("Depth First Search");

    std::string graph_txt("AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7");
    Directed_Graph g(graph_txt); // exercise sheet

    Depth_First_Search dfs(&g);
    // exercise sheet task 6
    ASSERT_EQUAL(dfs.get_num_paths_by_max_stops("C", "C", 3), 2);
    
    // there is no incoming edge to a, so there is no route
    ASSERT_EQUAL(dfs.get_num_paths_by_max_stops("A", "A", 10), 0); 

    ASSERT_EQUAL(dfs.get_num_paths_by_max_stops("B", "B", 3), 1); 
    ASSERT_EQUAL(dfs.get_num_paths_by_max_stops("B", "B", 4), 2); 
    ASSERT_EQUAL(dfs.get_num_paths_by_max_stops("B", "B", 6), 5); 

    // exercise sheet task 7
    ASSERT_EQUAL(dfs.get_num_paths_by_equal_stops("A", "C", 4), 3);


    // excercise sheet task 10
    ASSERT_EQUAL(dfs.get_num_paths_by_max_dist("C", "C", 30), 7);

    ASSERT_EQUAL(dfs.get_num_paths_by_max_dist("A", "A", 30), 0);
    ASSERT_EQUAL(dfs.get_num_paths_by_max_dist("A", "D", 18), 2);
    ASSERT_EQUAL(dfs.get_num_paths_by_max_dist("A", "D", 28), 6);

    EXPECT_EXCEPTION(dfs.get_num_paths_by_max_stops("", "A", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs.get_num_paths_by_max_stops("A", "1", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs.get_num_paths_by_max_dist("", "A", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs.get_num_paths_by_max_dist("A", "1", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs.get_num_paths_by_equal_stops("", "A", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs.get_num_paths_by_equal_stops("A", "1", 3), std::invalid_argument);

    EXPECT_EXCEPTION(dfs.get_num_paths_by_max_dist("A", "B", -3), std::invalid_argument);



    std::string graph_txt2("AA1");
    Directed_Graph g2(graph_txt2);
    Depth_First_Search dfs2(&g2);
    ASSERT_EQUAL(dfs2.get_num_paths_by_max_stops("A", "A", 1), 1);
    ASSERT_EQUAL(dfs2.get_num_paths_by_max_stops("A", "A", 2), 2);
    ASSERT_EQUAL(dfs2.get_num_paths_by_max_stops("A", "A", 3), 3);
    ASSERT_EQUAL(dfs2.get_num_paths_by_max_stops("A", "A", 10), 10);

    ASSERT_EQUAL(dfs2.get_num_paths_by_equal_stops("A", "A", 1), 1);
    ASSERT_EQUAL(dfs2.get_num_paths_by_equal_stops("A", "A", 2), 1);
    ASSERT_EQUAL(dfs2.get_num_paths_by_equal_stops("A", "A", 3), 1);
    ASSERT_EQUAL(dfs2.get_num_paths_by_equal_stops("A", "A", 11), 1);

    // the task specifically says that paths cannot be exactly max distance and be allowed
    ASSERT_EQUAL(dfs2.get_num_paths_by_max_dist("A", "A", 1), 0);
    ASSERT_EQUAL(dfs2.get_num_paths_by_max_dist("A", "A", 2), 1);

    std::string graph_txt3(""); // empty graph
    Directed_Graph g3(graph_txt3);
    Depth_First_Search dfs3(&g3);
    EXPECT_EXCEPTION(dfs3.get_num_paths_by_max_stops("A", "B", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs3.get_num_paths_by_equal_stops("A", "B", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs3.get_num_paths_by_max_dist("A", "B", 3), std::invalid_argument);

    EXPECT_EXCEPTION(dfs3.get_num_paths_by_max_stops("", "", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs3.get_num_paths_by_equal_stops("", "", 3), std::invalid_argument);
    EXPECT_EXCEPTION(dfs3.get_num_paths_by_max_dist("", "", 3), std::invalid_argument);

    std::string graph_txt4("AA1, BB1, AB1, BA1");
    Directed_Graph g4(graph_txt4);
    Depth_First_Search dfs4(&g4);
    ASSERT_EQUAL(dfs4.get_num_paths_by_max_stops("A", "A", 1), 1);
    ASSERT_EQUAL(dfs4.get_num_paths_by_max_stops("A", "A", 2), 3);
    ASSERT_EQUAL(dfs4.get_num_paths_by_equal_stops("A", "A", 2), 2);
    ASSERT_EQUAL(dfs4.get_num_paths_by_equal_stops("A", "A", 3), 4);
    ASSERT_EQUAL(dfs4.get_num_paths_by_max_dist("A", "A", 3), 3);

    TEST_END();
}

int main(int argc, char* argv[]) {
    bool t1 = test();
    return t1;
}
