#include "../include/simple_test.h"

AddTestUnit(Test1, "A test for testing unit tests") {
    EXPECT_EQ(2, 2);
    EXPECT_EQ(1, 2);
    ASSERT_EQ(2,2);
}

AddTestUnit(Test1A, "A test for testing unit tests") {
    class foo {};
    foo a;
    auto &&b = a;
    int &&i = 1;
    ASSERT_IS(a,b);
}

