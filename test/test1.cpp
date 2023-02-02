#include "../include/simple_test.h"

AddTestUnit(Test1, "A test for testing unit tests") {
    EXPECT_EQ(2, 2);
    EXPECT_EQ(1, 2) << "这是追加消息\n";
}

AddTestUnit(Test1A, "A test for testing unit tests") {
    std::cout<<"hello test"<<std::endl;
}
