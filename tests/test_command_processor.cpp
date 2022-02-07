#include <vector>
#include <string>
#include "test_base.h"
#include "../src/command_processor.h"
#include <stdexcept>

bool test() {
    TEST_BEGIN("command_processor");

    Command_Processor cp;
    ASSERT_EQUAL(cp.check_for_graph(), false);

    // none of the other functions actually return something
    // so we just test if all the exceptions are thrown correctly
    // we already know that the cmds themselves work through the other
    // tests

    // no graph set
    EXPECT_EXCEPTION(cp.cmd_length_of_path("A-B"), std::domain_error);
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_stops_smaller_than("A B"), std::domain_error);
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_stops_equal_to("A B"), std::domain_error);
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_distance_smaller_than("A B"), std::domain_error);
    EXPECT_EXCEPTION(cp.cmd_length_shortest_path("A B"), std::domain_error);

    EXPECT_EXCEPTION(cp.cmd_create_graph("2, AB3,"), std::invalid_argument);

    cp.cmd_create_graph("");

    // not enough arguments
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_stops_smaller_than("A B"), std::invalid_argument);
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_stops_equal_to("A B"), std::invalid_argument);
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_distance_smaller_than("A B"), std::invalid_argument);
    EXPECT_EXCEPTION(cp.cmd_length_shortest_path("A"), std::invalid_argument);

    // negative stops or distance
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_stops_smaller_than("A B -1"), std::invalid_argument);
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_stops_equal_to("A B -1"), std::invalid_argument);
    EXPECT_EXCEPTION(cp.cmd_number_of_paths_with_distance_smaller_than("A B -1"), std::invalid_argument);


    TEST_END();
}

int main(int argc, char* argv[]) {
    bool t1 = test();
    return t1;
}
