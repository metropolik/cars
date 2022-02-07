#include <vector>
#include <string>
#include "test_base.h"
#include "../src/utils.h"
#include <stdexcept>

bool test() {
    TEST_BEGIN("utils");

    std::string ss1("a b c");
    std::string ss2("a b ");
    std::string graph_txt("ab5, bc4, cd8, dc8, de6, ad5, ce2, eb3, ae7");
    std::string graph_txt2("ab5, bc4, cd8, dc8, de6, ad5, ce2, eb3, ae7, ");

    ASSERT_EQUAL(split_string_by_space(ss1).size(), 3);
    ASSERT_EQUAL(split_string_by_space(ss2).size(), 2);
    ASSERT_EQUAL(split_string_by(graph_txt, ", ").size(), 9);
    ASSERT_EQUAL(split_string_by(graph_txt, ", ").size(), 9);

    TEST_END();
}

int main(int argc, char* argv[]) {
    bool t1 = test();
    return t1;
}
